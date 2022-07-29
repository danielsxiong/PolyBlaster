// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PBCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "HUD/OverheadWidget.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Sound/SoundCue.h"
#include "Particles/ParticleSystemComponent.h"

#include "../PolyBlaster.h"
#include "Weapon/Weapon.h"
#include "Weapon/WeaponTypes.h"
#include "PBComponents/CombatComponent.h"
#include "PBComponents/BuffComponent.h"
#include "Character/PBAnimInstance.h"
#include "PlayerController/PBPlayerController.h"
#include "PlayerState/PBPlayerState.h"
#include "GameMode/PBGameMode.h"

APBCharacter::APBCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	OverheadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadWidget"));
	OverheadWidget->SetupAttachment(RootComponent);

	// Components doesn't need to be registered to GetLifetimeReplicatedProps
	Combat = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
	Combat->SetIsReplicated(true);

	Buff = CreateDefaultSubobject<UBuffComponent>(TEXT("BuffComponent"));
	Buff->SetIsReplicated(true);

	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 0.f, 650.f);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionObjectType(ECC_SkeletalMesh);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);

	TurningInPlace = ETurningInPlace::ETIP_NotTurning;
	NetUpdateFrequency = 66.f;
	MinNetUpdateFrequency = 33.f;

	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	DissolveTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("DissolveTimelineComponent"));

	AttachedGrenade = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AttachedGrenade"));
	AttachedGrenade->SetupAttachment(GetMesh(), FName("GrenadeSocket"));
	AttachedGrenade->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APBCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Should be replicated only to the owner, will cause everybody to see the pickup widget if it's replicated to everyone
	DOREPLIFETIME_CONDITION(APBCharacter, OverlappingWeapon, COND_OwnerOnly);
	//DOREPLIFETIME(APBCharacter, OverlappingWeapon);
	DOREPLIFETIME(APBCharacter, Health);
	DOREPLIFETIME(APBCharacter, Shield);
	DOREPLIFETIME(APBCharacter, bDisableGameplay);
}

void APBCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (Combat)
	{
		Combat->Character = this;
	}

	if (Buff)
	{
		Buff->Character = this;
		Buff->SetInitialSpeeds(GetCharacterMovement()->MaxWalkSpeed, GetCharacterMovement()->MaxWalkSpeedCrouched);
		Buff->SetInitialJumpVelocity(GetCharacterMovement()->JumpZVelocity);
	}
}

void APBCharacter::BeginPlay()
{
	Super::BeginPlay();

	SpawnDefaultWeapon();

	UpdateHUDAmmo();
	UpdateHUDHealth();
	UpdateHUDShield();

	if (HasAuthority())
	{
		OnTakeAnyDamage.AddDynamic(this, &APBCharacter::ReceiveDamage);
	}

	if (AttachedGrenade)
	{
		AttachedGrenade->SetVisibility(false);
	}
}

// Called to bind functionality to input
void APBCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APBCharacter::Jump);
	PlayerInputComponent->BindAction("Equip", IE_Pressed, this, &APBCharacter::EquipButtonPressed);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &APBCharacter::CrouchButtonPressed);
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &APBCharacter::AimButtonPressed);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &APBCharacter::AimButtonReleased);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APBCharacter::FireButtonPressed);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APBCharacter::FireButtonReleased);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &APBCharacter::ReloadButtonPressed);
	PlayerInputComponent->BindAction("ThrowGrenade", IE_Pressed, this, &APBCharacter::ThrowGrenadeButtonPressed);

	PlayerInputComponent->BindAxis("MoveForward", this, &APBCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APBCharacter::MoveRight);
	PlayerInputComponent->BindAxis("TurnMouse", this, &APBCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUpMouse", this, &APBCharacter::LookUp);
	PlayerInputComponent->BindAxis("TurnGamepad", this, &APBCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUpGamepad", this, &APBCharacter::LookUp);
}

void APBCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateInPlace(DeltaTime);

	HideCameraIfCharacterClose();
	PollInit();
}

void APBCharacter::SpawnDefaultWeapon()
{
	// If this map is a game map, spawn default weapon
	APBGameMode* PBGameMode = Cast<APBGameMode>(UGameplayStatics::GetGameMode(this));
	UWorld* World = GetWorld();
	if (PBGameMode && World && !bEliminated && DefaultWeaponClass)
	{
		AWeapon* StartingWeapon = World->SpawnActor<AWeapon>(DefaultWeaponClass);
		StartingWeapon->bDestroyWeapon = true;

		if (Combat)
		{
			Combat->EquipWeapon(StartingWeapon);	
		}
	}
}

void APBCharacter::RotateInPlace(float DeltaTime)
{
	if (bDisableGameplay)
	{
		bUseControllerRotationYaw = false;
		TurningInPlace = ETurningInPlace::ETIP_NotTurning;
		return;
	}

	if (GetLocalRole() > ENetRole::ROLE_SimulatedProxy && IsLocallyControlled())
	{
		AimOffset(DeltaTime);
	}
	else
	{
		TimeSinceLastMovementReplication += DeltaTime;
		if (TimeSinceLastMovementReplication > 0.25f)
		{
			OnRep_ReplicatedMovement();
		}
		CalculateAO_Pitch();
	}
}

void APBCharacter::Jump()
{
	if (bDisableGameplay) return;

	if (bIsCrouched)
	{
		UnCrouch();
	}
	else
	{
		Super::Jump();
	}
}

void APBCharacter::OnRep_ReplicatedMovement()
{
	Super::OnRep_ReplicatedMovement();

	SimProxiesTurn();
	TimeSinceLastMovementReplication = 0.f;
}

void APBCharacter::MoveForward(float Value)
{
	if (bDisableGameplay) return;

	if (Controller && Value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
		AddMovementInput(Direction, Value);
	}
}

void APBCharacter::MoveRight(float Value)
{
	if (bDisableGameplay) return;

	if (Controller && Value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));
		AddMovementInput(Direction, Value);
	}
}

void APBCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void APBCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void APBCharacter::EquipButtonPressed()
{
	if (bDisableGameplay) return;

	// Must only be done on server (Role Authority)
	if (Combat)
	{
		ServerEquipButtonPressed();
	}
}

void APBCharacter::ServerEquipButtonPressed_Implementation()
{
	// Must only be done on server (Role Authority)
	if (Combat)
	{
		if (OverlappingWeapon)
		{
			Combat->EquipWeapon(OverlappingWeapon);
		}
		else if (Combat->ShouldSwapWeapon())
		{
			Combat->SwapWeapon();
		}
	}
}

void APBCharacter::CrouchButtonPressed()
{
	if (bDisableGameplay) return;

	if (bIsCrouched)
	{
		UnCrouch();
	}
	else
	{
		Crouch();
	}
}

void APBCharacter::AimButtonPressed()
{
	if (bDisableGameplay || !Combat) return;

	Combat->SetAiming(true);
}

void APBCharacter::AimButtonReleased()
{
	if (bDisableGameplay || !Combat) return;

	Combat->SetAiming(false);
}

void APBCharacter::FireButtonPressed()
{
	if (bDisableGameplay || !Combat) return;

	Combat->FireButtonPressed(true);
}

void APBCharacter::FireButtonReleased()
{
	if (bDisableGameplay || !Combat) return;

	Combat->FireButtonPressed(false);
}

void APBCharacter::ReloadButtonPressed()
{
	if (bDisableGameplay || !Combat) return;

	Combat->Reload();
}

void APBCharacter::ThrowGrenadeButtonPressed()
{
	if (bDisableGameplay || !Combat) return;

	Combat->ThrowGrenade();
}

void APBCharacter::AimOffset(float DeltaTime)
{
	if (Combat && !Combat->EquippedWeapon) return;

	float Speed = CalculateSpeed();
	bool bIsInAir = GetCharacterMovement()->IsFalling();

	if (Speed == 0.f && !bIsInAir) // Standing still, not jumping
	{
		bRotateRootBone = true;
		FRotator CurrentAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
		FRotator DeltaAimRotation = UKismetMathLibrary::NormalizedDeltaRotator(CurrentAimRotation, StartingAimRotation);

		AO_Yaw = DeltaAimRotation.Yaw;

		if (TurningInPlace == ETurningInPlace::ETIP_NotTurning)
		{
			InterpAO_Yaw = AO_Yaw;
		}

		bUseControllerRotationYaw = true;

		TurnInPlace(DeltaTime);
		// UE_LOG(LogTemp, Warning, TEXT("AO_Yaw: %f"), AO_Yaw);
	}

	if (Speed > 0.f || bIsInAir) // Running, or jumping
	{
		bRotateRootBone = false;
		StartingAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
		
		AO_Yaw = 0.f;
		bUseControllerRotationYaw = true;
		TurningInPlace = ETurningInPlace::ETIP_NotTurning;
	}

	CalculateAO_Pitch();
}

void APBCharacter::CalculateAO_Pitch()
{
	AO_Pitch = GetBaseAimRotation().Pitch;
	if (AO_Pitch > 90.f && !IsLocallyControlled())
	{
		// map pitch from [270, 360) to [-90, 0)
		FVector2D InRange(270.f, 360.f);
		FVector2D OutRange(-90.f, 0.f);
		AO_Pitch = FMath::GetMappedRangeValueClamped(InRange, OutRange, AO_Pitch);
	}
}

void APBCharacter::SimProxiesTurn()
{
	if (!Combat || !Combat->EquippedWeapon) return;

	bRotateRootBone = false;

	float Speed = CalculateSpeed();
	if (Speed > 0.f)
	{
		TurningInPlace = ETurningInPlace::ETIP_NotTurning;
		return;
	}

	ProxyRotationLastFrame = ProxyRotation;
	ProxyRotation = GetActorRotation();
	ProxyYaw = UKismetMathLibrary::NormalizedDeltaRotator(ProxyRotation, ProxyRotationLastFrame).Yaw;

	// UE_LOG(LogTemp, Warning, TEXT("ProxyYaw: %f"), ProxyYaw);

	if (FMath::Abs(ProxyYaw) > TurnThreshold)
	{
		if (ProxyYaw > TurnThreshold)
		{
			TurningInPlace = ETurningInPlace::ETIP_Right;
		}
		else if (ProxyYaw < -TurnThreshold)
		{
			TurningInPlace = ETurningInPlace::ETIP_Left;
		}
		else
		{
			TurningInPlace = ETurningInPlace::ETIP_NotTurning;
		}

		return;
	}

	TurningInPlace = ETurningInPlace::ETIP_NotTurning;
}

void APBCharacter::HideCameraIfCharacterClose()
{
	if (!IsLocallyControlled()) return;

	if ((FollowCamera->GetComponentLocation() - GetActorLocation()).Size() < CameraThreshold)
	{
		GetMesh()->SetVisibility(false);
		if (Combat && Combat->EquippedWeapon && Combat->EquippedWeapon->GetWeaponMesh())
		{
			Combat->EquippedWeapon->GetWeaponMesh()->bOwnerNoSee = true;
		}
	}
	else
	{
		GetMesh()->SetVisibility(true);
		if (Combat && Combat->EquippedWeapon && Combat->EquippedWeapon->GetWeaponMesh())
		{
			Combat->EquippedWeapon->GetWeaponMesh()->bOwnerNoSee = false;
		}
	}
}

void APBCharacter::TurnInPlace(float DeltaTime)
{
	if (AO_Yaw > TurnThreshold)
	{
		TurningInPlace = ETurningInPlace::ETIP_Right;
	}
	else if (AO_Yaw < -TurnThreshold)
	{
		TurningInPlace = ETurningInPlace::ETIP_Left;
	}

	if (TurningInPlace != ETurningInPlace::ETIP_NotTurning)
	{
		InterpAO_Yaw = FMath::FInterpTo(InterpAO_Yaw, 0.f, DeltaTime, 4.f);
		AO_Yaw = InterpAO_Yaw;

		if (FMath::Abs(AO_Yaw) < 15.f)
		{
			TurningInPlace = ETurningInPlace::ETIP_NotTurning;
			StartingAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
		}
	}
}

void APBCharacter::PlayFireMontage(bool bAiming)
{
	if (!Combat || !Combat->EquippedWeapon) return;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && FireWeaponMontage)
	{
		AnimInstance->Montage_Play(FireWeaponMontage);
		FName SectionName;
		SectionName = bAiming ? FName("RifleAim") : FName("RifleHip");
		AnimInstance->Montage_JumpToSection(SectionName);
	}
}

void APBCharacter::PlayEliminatedMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && EliminatedMontage)
	{
		AnimInstance->Montage_Play(EliminatedMontage);
	}
}

void APBCharacter::PlayReloadMontage()
{
	if (!Combat || !Combat->EquippedWeapon) return;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && ReloadMontage)
	{
		AnimInstance->Montage_Play(ReloadMontage);
		FName SectionName;
		switch (Combat->EquippedWeapon->GetWeaponType())
		{
		case EWeaponType::EWT_AssaultRifle:
		{
			SectionName = FName("Rifle");
			break;
		}
		case EWeaponType::EWT_RocketLauncher:
		{
			SectionName = FName("RocketLauncher");
			break;
		}
		case EWeaponType::EWT_Pistol:
		{
			SectionName = FName("Pistol");
			break;
		}
		case EWeaponType::EWT_SubmachineGun:
		{
			SectionName = FName("Pistol");
			break;
		}
		case EWeaponType::EWT_Shotgun:
		{
			SectionName = FName("Shotgun");
			break;
		}
		case EWeaponType::EWT_SniperRifle:
		{
			SectionName = FName("SniperRifle");
			break;
		}
		case EWeaponType::EWT_GrenadeLauncher:
		{
			SectionName = FName("Rifle");
			break;
		}
		}
		AnimInstance->Montage_JumpToSection(SectionName);
	}
}

void APBCharacter::PlayThrowGrenadeMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && ThrowGrenadeMontage)
	{
		AnimInstance->Montage_Play(ThrowGrenadeMontage);
	}
}

void APBCharacter::MulticastEliminated_Implementation()
{
	bEliminated = true;
	PlayEliminatedMontage();

	// Start dissolve effect
	if (DissolveMaterialInstance)
	{
		DynamicDissolveMaterialInstance = UMaterialInstanceDynamic::Create(DissolveMaterialInstance, this);
		GetMesh()->SetMaterial(0, DynamicDissolveMaterialInstance);
		DynamicDissolveMaterialInstance->SetScalarParameterValue(TEXT("Dissolve"), 0.f);
		DynamicDissolveMaterialInstance->SetScalarParameterValue(TEXT("Glow"), 200.f);
	}

	StartDissolve();

	// Disable character movement
	GetCharacterMovement()->DisableMovement();
	GetCharacterMovement()->StopMovementImmediately();

	// Delay removing collision to avoid rocket launcher passing through on client
	GetWorldTimerManager().SetTimer(DisableCollisionTimer, this, &APBCharacter::DisableCollisionTimerFinished, DisableCollisionDelay);

	bDisableGameplay = true;

	if (Combat)
	{
		Combat->FireButtonPressed(false);
	}

	if (PBPlayerController)
	{
		// Also set ammo HUD to 0
		PBPlayerController->SetHUDWeaponAmmo(0);
	}

	// Spawn Elim Bot
	if (ElimBotEffect)
	{
		FVector ElimBotSpawnPoint(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 200.f);
		ElimBotComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ElimBotEffect, ElimBotSpawnPoint, GetActorRotation());
	}

	if (ElimBotSound)
	{
		UGameplayStatics::SpawnSoundAtLocation(this, ElimBotSound, GetActorLocation());
	}

	bool bHideSniperScope = IsLocallyControlled() && Combat && Combat->bAiming && Combat->EquippedWeapon && Combat->EquippedWeapon->GetWeaponType() == EWeaponType::EWT_SniperRifle;
	if (bHideSniperScope)
	{
		ShowSniperScopeWidget(false);
	}
}

void APBCharacter::Eliminated()
{
	if (bEliminated) return;

	if (Combat && Combat->EquippedWeapon)
	{
		if (!Combat->EquippedWeapon->bDestroyWeapon)
		{
			Combat->EquippedWeapon->Drop();
		}
		else
		{
			Combat->EquippedWeapon->Destroy();
		}
		Combat->EquippedWeapon = nullptr;
	}

	MulticastEliminated();

	GetWorldTimerManager().SetTimer(EliminatedTimer, this, &APBCharacter::EliminatedTimerFinished, EliminatedDelay);
}

void APBCharacter::EliminatedTimerFinished()
{
	APBGameMode* PBGameMode = GetWorld()->GetAuthGameMode<APBGameMode>();
	if (PBGameMode)
	{
		PBGameMode->RequestRespawn(this, Controller);
	}
}

void APBCharacter::DisableCollisionTimerFinished()
{
	// Disable collision
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APBCharacter::UpdateDissolveMaterial(float DissolveValue)
{
	if (DynamicDissolveMaterialInstance)
	{
		DynamicDissolveMaterialInstance->SetScalarParameterValue(TEXT("Dissolve"), DissolveValue);
	}
}

void APBCharacter::StartDissolve()
{
	DissolveTrack.BindDynamic(this, &APBCharacter::UpdateDissolveMaterial);
	if (DissolveCurve)
	{
		DissolveTimeline->AddInterpFloat(DissolveCurve, DissolveTrack);
		DissolveTimeline->Play();
	}
}

void APBCharacter::PlayHitReactMontage()
{
	if (!Combat || !Combat->EquippedWeapon) return;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && HitReactMontage)
	{
		AnimInstance->Montage_Play(HitReactMontage);
		FName SectionName("FromFront");
		//SectionName = bAiming ? FName("RifleAim") : FName("RifleHip");
		AnimInstance->Montage_JumpToSection(SectionName);
	}
}

void APBCharacter::ReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatorController, AActor* DamageCauser)
{
	if (bEliminated) return;
	/*if (Combat)
	{
		Combat->SetCombatState(ECombatState::ECS_Unoccupied);
	}*/

	float DamageToHealth = Damage;
	if (Shield > 0.f)
	{
		if (Shield >= Damage)
		{
			Shield = FMath::Clamp(Shield - Damage, 0.f, MaxShield);
			DamageToHealth = 0.f;
		}
		else
		{
			DamageToHealth = FMath::Clamp(DamageToHealth - Shield, 0.f, Damage);
			Shield = 0.f;
		}
	}
	Health = FMath::Clamp(Health - DamageToHealth, 0.f, MaxHealth);

	PlayHitReactMontage();
	UpdateHUDHealth();
	UpdateHUDShield();

	if (Health == 0.f)
	{
		APBGameMode* PBGameMode = GetWorld()->GetAuthGameMode<APBGameMode>();
		if (PBGameMode)
		{
			PBPlayerController = PBPlayerController == nullptr ? Cast<APBPlayerController>(Controller) : PBPlayerController;
			APBPlayerController* AttackerController = Cast<APBPlayerController>(InstigatorController);
			PBGameMode->PlayerEliminated(this, PBPlayerController, AttackerController);
		}
	}
}

//void APBCharacter::MulticastHit_Implementation()
//{
//	PlayHitReactMontage();
//}

void APBCharacter::OnRep_Health(float LastHealth)
{
	if (Health < LastHealth)
	{
		PlayHitReactMontage();
	}
	
	UpdateHUDHealth();
}

void APBCharacter::OnRep_Shield(float LastShield)
{
	if (Shield < LastShield)
	{
		PlayHitReactMontage();
	}

	UpdateHUDShield();
}

void APBCharacter::UpdateHUDHealth()
{
	PBPlayerController = PBPlayerController == nullptr ? Cast<APBPlayerController>(Controller) : PBPlayerController;
	if (PBPlayerController)
	{
		PBPlayerController->SetHUDHealth(Health, MaxHealth);
	}
}

void APBCharacter::UpdateHUDShield()
{
	PBPlayerController = PBPlayerController == nullptr ? Cast<APBPlayerController>(Controller) : PBPlayerController;
	if (PBPlayerController)
	{
		PBPlayerController->SetHUDShield(Shield, MaxShield);
	}
}

void APBCharacter::UpdateHUDAmmo()
{
	PBPlayerController = PBPlayerController == nullptr ? Cast<APBPlayerController>(Controller) : PBPlayerController;
	if (PBPlayerController && Combat && Combat->EquippedWeapon)
	{
		PBPlayerController->SetHUDCarriedAmmo(Combat->CarriedAmmo);
		PBPlayerController->SetHUDWeaponAmmo(Combat->EquippedWeapon->GetAmmo());
	}
}

void APBCharacter::PollInit()
{
	if (!PBPlayerState)
	{
		PBPlayerState = GetPlayerState<APBPlayerState>();
		if (PBPlayerState)
		{
			PBPlayerState->AddToScore(0.f);
			PBPlayerState->AddToDefeats(0);
		}
	}
}

void APBCharacter::SetOverlappingWeapon(AWeapon* InWeapon)
{
	// Remove the pickup widget from the previous overlapping weapon, if exist
	if (OverlappingWeapon)
	{
		OverlappingWeapon->ShowPickupWidget(false);
	}

	// Set the new overlapping weapon, it will call OnRep_OverlappingWeapon
	OverlappingWeapon = InWeapon;

	// Only show pickup widget if it's on player's local machine
	if (IsLocallyControlled())
	{
		if (OverlappingWeapon)
		{
			OverlappingWeapon->ShowPickupWidget(true);
		}
	}
}

void APBCharacter::OnRep_OverlappingWeapon(AWeapon* LastWeapon)
{
	// 
	if (OverlappingWeapon)
	{
		OverlappingWeapon->ShowPickupWidget(true);
	}

	if (LastWeapon)
	{
		LastWeapon->ShowPickupWidget(false);
	}
}

float APBCharacter::CalculateSpeed()
{
	FVector Velocity = GetVelocity();
	Velocity.Z = 0.f;
	return Velocity.Size();
}

bool APBCharacter::IsWeaponEquipped()
{
	return Combat && Combat->EquippedWeapon;
}

bool APBCharacter::IsAiming()
{
	return Combat && Combat->bAiming;
}

AWeapon* APBCharacter::GetEquippedWeapon()
{
	if (!Combat) return nullptr;

	return Combat->EquippedWeapon;
}

FVector APBCharacter::GetHitTarget() const
{
	if (!Combat)
	{
		return FVector();
	}

	return Combat->HitTarget;
}

ECombatState APBCharacter::GetCombatState() const
{
	if (!Combat)
	{
		return ECombatState::ECS_MAX;
	}

	return Combat->CombatState;
}

void APBCharacter::Destroyed()
{
	Super::Destroyed();

	if (ElimBotComponent)
	{
		ElimBotComponent->DestroyComponent();
	}

	APBGameMode* PBGameMode = Cast<APBGameMode>(UGameplayStatics::GetGameMode(this));
	bool bMatchNotInProgress = PBGameMode && PBGameMode->GetMatchState() != MatchState::InProgress;

	if (Combat && Combat->EquippedWeapon && bMatchNotInProgress)
	{
		Combat->EquippedWeapon->Destroy();
	}
}