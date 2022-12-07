// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PBCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "HUD/OverheadWidget.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Sound/SoundCue.h"
#include "Particles/ParticleSystemComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

#include "../PolyBlaster.h"
#include "Weapon/Weapon.h"
#include "Weapon/WeaponTypes.h"
#include "PBComponents/CombatComponent.h"
#include "PBComponents/BuffComponent.h"
#include "PBComponents/LagCompensationComponent.h"
#include "Character/PBAnimInstance.h"
#include "PlayerController/PBPlayerController.h"
#include "PlayerState/PBPlayerState.h"
#include "GameMode/PBGameMode.h"
#include "GameState/PBGameState.h"
#include "PlayerStart/TeamPlayerStart.h"

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

	LagCompensation = CreateDefaultSubobject<ULagCompensationComponent>(TEXT("LagCompensation"));

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

	/**
	* Hit boxes for server side rewind
	*/

	HeadBox = CreateDefaultSubobject<UBoxComponent>(TEXT("head"));
	HeadBox->SetupAttachment(GetMesh(), FName("head"));
	HitCollisionBoxes.Add(FName("head"), HeadBox);

	PelvisBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Pelvis"));
	PelvisBox->SetupAttachment(GetMesh(), FName("Pelvis"));
	HitCollisionBoxes.Add(FName("Pelvis"), PelvisBox);

	Spine02Box = CreateDefaultSubobject<UBoxComponent>(TEXT("spine_02"));
	Spine02Box->SetupAttachment(GetMesh(), FName("spine_02"));
	HitCollisionBoxes.Add(FName("spine_02"), Spine02Box);

	Spine03Box = CreateDefaultSubobject<UBoxComponent>(TEXT("spine_03"));
	Spine03Box->SetupAttachment(GetMesh(), FName("spine_03"));
	HitCollisionBoxes.Add(FName("spine_03"), Spine03Box);

	UpperArm_LBox = CreateDefaultSubobject<UBoxComponent>(TEXT("UpperArm_L"));
	UpperArm_LBox->SetupAttachment(GetMesh(), FName("UpperArm_L"));
	HitCollisionBoxes.Add(FName("UpperArm_L"), UpperArm_LBox);

	UpperArm_RBox = CreateDefaultSubobject<UBoxComponent>(TEXT("UpperArm_R"));
	UpperArm_RBox->SetupAttachment(GetMesh(), FName("UpperArm_R"));
	HitCollisionBoxes.Add(FName("UpperArm_R"), UpperArm_RBox);

	LowerArm_LBox = CreateDefaultSubobject<UBoxComponent>(TEXT("lowerarm_l"));
	LowerArm_LBox->SetupAttachment(GetMesh(), FName("lowerarm_l"));
	HitCollisionBoxes.Add(FName("lowerarm_l"), LowerArm_LBox);

	LowerArm_RBox = CreateDefaultSubobject<UBoxComponent>(TEXT("lowerarm_r"));
	LowerArm_RBox->SetupAttachment(GetMesh(), FName("lowerarm_r"));
	HitCollisionBoxes.Add(FName("lowerarm_r"), LowerArm_RBox);

	Hand_LBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hand_L"));
	Hand_LBox->SetupAttachment(GetMesh(), FName("Hand_L"));
	HitCollisionBoxes.Add(FName("Hand_L"), Hand_LBox);

	Hand_RBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hand_R"));
	Hand_RBox->SetupAttachment(GetMesh(), FName("Hand_R"));
	HitCollisionBoxes.Add(FName("Hand_R"), Hand_RBox);

	Thigh_LBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Thigh_L"));
	Thigh_LBox->SetupAttachment(GetMesh(), FName("Thigh_L"));
	HitCollisionBoxes.Add(FName("Thigh_L"), Thigh_LBox);

	Thigh_RBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Thigh_R"));
	Thigh_RBox->SetupAttachment(GetMesh(), FName("Thigh_R"));
	HitCollisionBoxes.Add(FName("Thigh_R"), Thigh_RBox);

	Calf_LBox = CreateDefaultSubobject<UBoxComponent>(TEXT("calf_l"));
	Calf_LBox->SetupAttachment(GetMesh(), FName("calf_l"));
	HitCollisionBoxes.Add(FName("calf_l"), Calf_LBox);

	Calf_RBox = CreateDefaultSubobject<UBoxComponent>(TEXT("calf_r"));
	Calf_RBox->SetupAttachment(GetMesh(), FName("calf_r"));
	HitCollisionBoxes.Add(FName("calf_r"), Calf_RBox);

	Foot_LBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Foot_L"));
	Foot_LBox->SetupAttachment(GetMesh(), FName("Foot_L"));
	HitCollisionBoxes.Add(FName("Foot_L"), Foot_LBox);

	Foot_RBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Foot_R"));
	Foot_RBox->SetupAttachment(GetMesh(), FName("Foot_R"));
	HitCollisionBoxes.Add(FName("Foot_R"), Foot_RBox);

	for (auto& Box : HitCollisionBoxes)
	{
		if (Box.Value)
		{
			Box.Value->SetCollisionObjectType(ECC_HitBox);
			Box.Value->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			Box.Value->SetCollisionResponseToChannel(ECC_HitBox, ECollisionResponse::ECR_Block);
			Box.Value->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
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

	if (LagCompensation)
	{
		LagCompensation->Character = this;
		if (Controller)
		{
			LagCompensation->Controller = Cast<APBPlayerController>(Controller);
		}
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

void APBCharacter::PollInit()
{
	if (!PBPlayerState)
	{
		PBPlayerState = GetPlayerState<APBPlayerState>();
		if (PBPlayerState)
		{
			OnPlayerStateInitialized();

			APBGameState* PBGameState = Cast<APBGameState>(UGameplayStatics::GetGameState(this));
			if (PBGameState && PBGameState->TopScoringPlayers.Contains(PBPlayerState))
			{
				MulticastGainedTheLead();
			}
		}
	}
}

void APBCharacter::OnPlayerStateInitialized()
{
	PBPlayerState->AddToScore(0.f);
	PBPlayerState->AddToDefeats(0);
	SetTeamColor(PBPlayerState->GetTeam());
	SetSpawnPoint();
}

void APBCharacter::SetSpawnPoint()
{
	if (HasAuthority() && PBPlayerState->GetTeam() != ETeam::ET_NoTeam)
	{
		TArray<AActor*> PlayerStarts;
		UGameplayStatics::GetAllActorsOfClass(this, ATeamPlayerStart::StaticClass(), PlayerStarts);

		TArray<ATeamPlayerStart*> TeamPlayerStarts;
		for (auto Start : PlayerStarts)
		{
			ATeamPlayerStart* TeamStart = Cast<ATeamPlayerStart>(Start);
			if (TeamStart && TeamStart->Team == PBPlayerState->GetTeam())
			{
				TeamPlayerStarts.Add(TeamStart);
			}
		}

		if (TeamPlayerStarts.Num() > 0)
		{
			int32 Selection = FMath::RandRange(0, TeamPlayerStarts.Num() - 1);
			ATeamPlayerStart* SelectedPlayerStart = TeamPlayerStarts[Selection];
			SetActorLocationAndRotation(SelectedPlayerStart->GetActorLocation(), SelectedPlayerStart->GetActorRotation());
		}
	}
}

void APBCharacter::SpawnDefaultWeapon()
{
	// If this map is a game map, spawn default weapon, this also makes sure that weapons are spawned on the server and not the client
	PBGameMode = PBGameMode == nullptr ? GetWorld()->GetAuthGameMode<APBGameMode>() : PBGameMode;

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

void APBCharacter::SetTeamColor(ETeam Team)
{
	if (!GetMesh() || !OriginalMaterial) return;
	switch (Team)
	{
	case ETeam::ET_NoTeam:
		GetMesh()->SetMaterial(0, OriginalMaterial);
		DissolveMaterialInstance = BlueDissolveMaterialInstance;
		break;
	case ETeam::ET_BlueTeam:
		GetMesh()->SetMaterial(0, BlueMaterial);
		DissolveMaterialInstance = BlueDissolveMaterialInstance;
		break;
	case ETeam::ET_RedTeam:
		GetMesh()->SetMaterial(0, RedMaterial);
		DissolveMaterialInstance = RedDissolveMaterialInstance;
		break;
	}
}

void APBCharacter::RotateInPlace(float DeltaTime)
{
	if (Combat && Combat->bHoldingTheFlag)
	{
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		TurningInPlace = ETurningInPlace::ETIP_NotTurning;
		return;
	}

	if (Combat && Combat->EquippedWeapon)
	{
		bUseControllerRotationYaw = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
	}

	if (bDisableGameplay)
	{
		bUseControllerRotationYaw = false;
		TurningInPlace = ETurningInPlace::ETIP_NotTurning;
		return;
	}

	/*if (GetLocalRole() > ENetRole::ROLE_SimulatedProxy && IsLocallyControlled())
	{
		AimOffset(DeltaTime);
	}
	else
	{*/
		TimeSinceLastMovementReplication += DeltaTime;
		if (TimeSinceLastMovementReplication > 0.25f)
		{
			OnRep_ReplicatedMovement();
		}
		CalculateAO_Pitch();
	//}
}

void APBCharacter::Jump()
{
	if (Combat && Combat->bHoldingTheFlag) return;
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

	if (Combat)
	{
		if (Combat->bHoldingTheFlag) return;
		if (Combat->CombatState == ECombatState::ECS_Unoccupied) ServerEquipButtonPressed(); // Must only be done on server (Role Authority)
		
		if (Combat->ShouldSwapWeapon() && 
			!HasAuthority() && 
			Combat->CombatState == ECombatState::ECS_Unoccupied && 
			!OverlappingWeapon) // Play swap animation on client first
		{
			PlaySwapMontage();
			Combat->CombatState = ECombatState::ECS_SwappingWeapons;
			bFinishedSwapping = false;
		}
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
	if (Combat && Combat->bHoldingTheFlag) return;

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
	if (Combat && Combat->bHoldingTheFlag) return;
	if (bDisableGameplay || !Combat) return;

	Combat->SetAiming(true);
}

void APBCharacter::AimButtonReleased()
{
	if (Combat && Combat->bHoldingTheFlag) return;
	if (bDisableGameplay || !Combat) return;

	Combat->SetAiming(false);
}

void APBCharacter::FireButtonPressed()
{
	if (Combat && Combat->bHoldingTheFlag) return;
	if (bDisableGameplay || !Combat) return;

	Combat->FireButtonPressed(true);
}

void APBCharacter::FireButtonReleased()
{
	if (Combat && Combat->bHoldingTheFlag) return;
	if (bDisableGameplay || !Combat) return;

	Combat->FireButtonPressed(false);
}

void APBCharacter::ReloadButtonPressed()
{
	if (Combat && Combat->bHoldingTheFlag) return;
	if (bDisableGameplay || !Combat) return;

	Combat->Reload();
}

void APBCharacter::ThrowGrenadeButtonPressed()
{
	if (Combat && Combat->bHoldingTheFlag) return;
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

		// TurnInPlace(DeltaTime);
		SimProxiesTurn();
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
		if (Combat && Combat->SecondaryWeapon && Combat->SecondaryWeapon->GetWeaponMesh())
		{
			Combat->SecondaryWeapon->GetWeaponMesh()->bOwnerNoSee = true;
		}
	}
	else
	{
		GetMesh()->SetVisibility(true);
		if (Combat && Combat->EquippedWeapon && Combat->EquippedWeapon->GetWeaponMesh())
		{
			Combat->EquippedWeapon->GetWeaponMesh()->bOwnerNoSee = false;
		}
		if (Combat && Combat->SecondaryWeapon && Combat->SecondaryWeapon->GetWeaponMesh())
		{
			Combat->SecondaryWeapon->GetWeaponMesh()->bOwnerNoSee = false;
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

void APBCharacter::PlaySwapMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && SwapMontage)
	{
		AnimInstance->Montage_Play(SwapMontage);
	}
}

void APBCharacter::MulticastEliminated_Implementation(bool bPlayerLeftGame)
{
	bEliminated = true;
	bLeftGame = bPlayerLeftGame;
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

	if (CrownComponent)
	{
		CrownComponent->DestroyComponent();
	}

	GetWorldTimerManager().SetTimer(EliminatedTimer, this, &APBCharacter::EliminatedTimerFinished, EliminatedDelay);
}

void APBCharacter::Eliminated(bool bPlayerLeftGame)
{
	if (bEliminated) return;

	if (Combat)
	{
		if (Combat->EquippedWeapon)
		{
			DropOrDestroyWeapon(Combat->EquippedWeapon);
		}
		
		if (Combat->SecondaryWeapon)
		{
			DropOrDestroyWeapon(Combat->SecondaryWeapon);
		}

		if (Combat->TheFlag)
		{
			DropOrDestroyWeapon(Combat->TheFlag);
		}
	}

	MulticastEliminated(bPlayerLeftGame);
}

void APBCharacter::DropOrDestroyWeapon(AWeapon* Weapon)
{
	if (Weapon)
	{
		if (!Weapon->bDestroyWeapon)
		{
			Weapon->Drop();
		}
		else
		{
			Weapon->Destroy();
		}

		Weapon = nullptr;
	}
}

void APBCharacter::EliminatedTimerFinished()
{
	PBGameMode = PBGameMode == nullptr ? GetWorld()->GetAuthGameMode<APBGameMode>() : PBGameMode;

	if (PBGameMode && !bLeftGame)
	{
		PBGameMode->RequestRespawn(this, Controller);
	}

	if (bLeftGame && IsLocallyControlled())
	{
		OnLeftGame.Broadcast();
	}
}

void APBCharacter::DisableCollisionTimerFinished()
{
	// Disable collision
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttachedGrenade->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APBCharacter::ServerLeaveGame_Implementation()
{
	PBGameMode = PBGameMode == nullptr ? GetWorld()->GetAuthGameMode<APBGameMode>() : PBGameMode;

	PBPlayerState = PBPlayerState == nullptr ? GetPlayerState<APBPlayerState>() : PBPlayerState;
	if (PBGameMode && PBPlayerState)
	{
		PBGameMode->PlayerLeftGame(PBPlayerState);
	}
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
	PBGameMode = PBGameMode == nullptr ? GetWorld()->GetAuthGameMode<APBGameMode>() : PBGameMode;

	if (bEliminated || !PBGameMode) return;

	Damage = PBGameMode->CalculateDamage(InstigatorController, Controller, Damage);

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

void APBCharacter::MulticastGainedTheLead_Implementation()
{
	if (!CrownSystem) return;

	if (!CrownComponent)
	{
		CrownComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
			CrownSystem, 
			GetMesh(), 
			FName(), 
			GetActorLocation() + FVector(0.f, 0.f, 110.f),
			GetActorRotation(), 
			EAttachLocation::KeepWorldPosition, false
		);
	}

	if (CrownComponent)
	{
		CrownComponent->Activate();
	}
}

void APBCharacter::MulticastLostTheLead_Implementation()
{
	if (CrownComponent)
	{
		CrownComponent->DestroyComponent();
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

bool APBCharacter::IsLocallyReloading() const
{
	if (!Combat) return false;

	return Combat->bLocallyReloading;
}

bool APBCharacter::IsHoldingTheFlag() const
{
	if (!Combat) return false;

	return Combat->bHoldingTheFlag;
}

void APBCharacter::SetHoldingTheFlag(bool bHolding)
{
	if (!Combat) return;

	Combat->bHoldingTheFlag = bHolding;
	Combat->TheFlag = nullptr;
	UnCrouch();
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

ETeam APBCharacter::GetTeam()
{
	PBPlayerState = PBPlayerState == nullptr ? GetPlayerState<APBPlayerState>() : PBPlayerState;
	if (PBPlayerState)
	{
		return PBPlayerState->GetTeam();
	}
	return ETeam::ET_NoTeam;
}

void APBCharacter::Destroyed()
{
	Super::Destroyed();

	if (ElimBotComponent)
	{
		ElimBotComponent->DestroyComponent();
	}

	PBGameMode = PBGameMode == nullptr ? GetWorld()->GetAuthGameMode<APBGameMode>() : PBGameMode;
	bool bMatchNotInProgress = PBGameMode && PBGameMode->GetMatchState() != MatchState::InProgress;

	if (Combat && Combat->EquippedWeapon && bMatchNotInProgress)
	{
		Combat->EquippedWeapon->Destroy();
	}
}