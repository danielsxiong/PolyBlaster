// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Weapon.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Net/UnrealNetwork.h"
#include "Animation/AnimationAsset.h"
#include "Kismet/KismetMathLibrary.h"

#include "Character/PBCharacter.h"
#include "PlayerController/PBPlayerController.h"
#include "Weapon/Casing.h"
#include "PBComponents/CombatComponent.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	SetReplicateMovement(true);

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);

	WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_BLUE);
	WeaponMesh->MarkRenderStateDirty();
	EnableCustomDepth(true);

	AreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphere"));
	AreaSphere->SetupAttachment(RootComponent);
	AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	PickupWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickupWidget"));
	PickupWidget->SetupAttachment(RootComponent);
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	// Only set collision enabled on server
	AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	AreaSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	AreaSphere->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnSphereOverlap);
	AreaSphere->OnComponentEndOverlap.AddDynamic(this, &AWeapon::OnSphereEndOverlap);

	ShowPickupWidget(false);
}

void AWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWeapon, WeaponState);
	DOREPLIFETIME_CONDITION(AWeapon, bUseServerSideRewind, COND_OwnerOnly);
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::OnRep_Owner()
{
	Super::OnRep_Owner();

	if (!Owner)
	{
		OwnerPBCharacter = nullptr;
		OwnerPBPlayerController = nullptr;
		return;
	}
	
	OwnerPBCharacter = OwnerPBCharacter == nullptr ? Cast<APBCharacter>(Owner) : OwnerPBCharacter;
	if (OwnerPBCharacter && OwnerPBCharacter->GetEquippedWeapon() && OwnerPBCharacter->GetEquippedWeapon() == this)
	{
		SetHUDAmmo();
	}
}

void AWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweep)
{
	APBCharacter* PBCharacter = Cast<APBCharacter>(OtherActor);
	if (PBCharacter && PickupWidget)
	{
		PBCharacter->SetOverlappingWeapon(this);
	}
}

void AWeapon::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APBCharacter* PBCharacter = Cast<APBCharacter>(OtherActor);
	if (PBCharacter && PickupWidget)
	{
		PBCharacter->SetOverlappingWeapon(nullptr);
	}
}

void AWeapon::Fire(const FVector& HitTarget)
{
	if (FireAnimation)
	{
		WeaponMesh->PlayAnimation(FireAnimation, false);
	}

	if (CasingClass)
	{
		const USkeletalMeshSocket* AmmoEjectSocket = GetWeaponMesh()->GetSocketByName(FName("AmmoEject"));
		if (AmmoEjectSocket)
		{
			FTransform SocketTransform = AmmoEjectSocket->GetSocketTransform(GetWeaponMesh());

			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;

			UWorld* World = GetWorld();
			if (World)
			{
				FRotator RandomShellRotator = FRotator(FMath::RandRange(0.f, 359.f), FMath::RandRange(0.f, 359.f), FMath::RandRange(0.f, 359.f));
				World->SpawnActor<ACasing>(CasingClass, SocketTransform.GetLocation(), RandomShellRotator, SpawnParams);
			}
		}
	}

	SpendRound();
}

void AWeapon::EnableCustomDepth(bool bEnable)
{
	if (WeaponMesh)
	{
		WeaponMesh->SetRenderCustomDepth(bEnable);
	}
}

FVector AWeapon::TraceEndWithScatter(const FVector& HitTarget)
{
	const USkeletalMeshSocket* MuzzleFlashSocket = GetWeaponMesh()->GetSocketByName("MuzzleFlash");
	if (!MuzzleFlashSocket) return FVector();

	const FTransform SocketTransform = MuzzleFlashSocket->GetSocketTransform(GetWeaponMesh());
	const FVector TraceStart = SocketTransform.GetLocation();

	const FVector ToTargetNormalized = (HitTarget - TraceStart).GetSafeNormal();
	const FVector SphereCenter = TraceStart + ToTargetNormalized * DistanceToSphere;
	const FVector RandVec = UKismetMathLibrary::RandomUnitVector() * FMath::FRandRange(0.f, SphereRadius);
	const FVector EndLoc = SphereCenter + RandVec;
	const FVector ToEndLoc = EndLoc - TraceStart;

	//DrawDebugSphere(GetWorld(), SphereCenter, SphereRadius, 12, FColor::Red, true);
	//DrawDebugSphere(GetWorld(), EndLoc, 4.f, 12, FColor::Orange, true);
	//DrawDebugLine(GetWorld(), TraceStart, FVector(TraceStart + ToEndLoc * TRACE_LENGTH / ToEndLoc.Size()), FColor::Cyan, true);

	return FVector(TraceStart + ToEndLoc * TRACE_LENGTH / ToEndLoc.Size());
}

void AWeapon::ShowPickupWidget(bool bShowPickupWidget)
{
	if (PickupWidget)
	{
		PickupWidget->SetVisibility(bShowPickupWidget);
	}
}

void AWeapon::SetWeaponState(EWeaponState InState)
{
	WeaponState = InState;

	OnWeaponStateSet();
}

void AWeapon::OnWeaponStateSet()
{
	switch (WeaponState)
	{
	case EWeaponState::EWS_Equipped:
	{
		OnEquipped();
		break;
	}
	case EWeaponState::EWS_EquippedSecondary:
	{
		OnEquippedSecondary();
		break;
	}
	case EWeaponState::EWS_Dropped:
	{
		OnDropped();
		break;
	}
	}
}

void AWeapon::OnRep_WeaponState()
{
	OnWeaponStateSet();
}

void AWeapon::OnEquipped()
{
	if (!AreaSphere || !WeaponMesh) return;

	ShowPickupWidget(false);
	AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	WeaponMesh->SetSimulatePhysics(false);
	WeaponMesh->SetEnableGravity(false);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (WeaponType == EWeaponType::EWT_SubmachineGun)
	{
		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		WeaponMesh->SetEnableGravity(true);
		WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	}

	EnableCustomDepth(true);

	OwnerPBCharacter = OwnerPBCharacter == nullptr ? Cast<APBCharacter>(GetOwner()) : OwnerPBCharacter;
	if (OwnerPBCharacter && bUseServerSideRewind)
	{
		OwnerPBPlayerController = OwnerPBPlayerController == nullptr ? Cast<APBPlayerController>(OwnerPBCharacter->Controller) : OwnerPBPlayerController;
		if (OwnerPBPlayerController && HasAuthority() && !OwnerPBPlayerController->HighPingDelegate.IsBound())
		{
			OwnerPBPlayerController->HighPingDelegate.AddDynamic(this, &AWeapon::OnPingTooHigh);
		}
	}
}

void AWeapon::OnEquippedSecondary()
{
	if (!AreaSphere || !WeaponMesh) return;

	ShowPickupWidget(false);
	AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	WeaponMesh->SetSimulatePhysics(false);
	WeaponMesh->SetEnableGravity(false);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (WeaponType == EWeaponType::EWT_SubmachineGun)
	{
		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		WeaponMesh->SetEnableGravity(true);
		WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	}

	WeaponMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_TAN);
	WeaponMesh->MarkRenderStateDirty();
	EnableCustomDepth(true);

	OwnerPBCharacter = OwnerPBCharacter == nullptr ? Cast<APBCharacter>(GetOwner()) : OwnerPBCharacter;
	if (OwnerPBCharacter && bUseServerSideRewind)
	{
		OwnerPBPlayerController = OwnerPBPlayerController == nullptr ? Cast<APBPlayerController>(OwnerPBCharacter->Controller) : OwnerPBPlayerController;
		if (OwnerPBPlayerController && HasAuthority() && OwnerPBPlayerController->HighPingDelegate.IsBound())
		{
			OwnerPBPlayerController->HighPingDelegate.RemoveDynamic(this, &AWeapon::OnPingTooHigh);
		}
	}
}

void AWeapon::OnDropped()
{
	if (HasAuthority())
	{
		AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}

	WeaponMesh->SetSimulatePhysics(true);
	WeaponMesh->SetEnableGravity(true);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	WeaponMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_BLUE);
	WeaponMesh->MarkRenderStateDirty();
	EnableCustomDepth(true);

	OwnerPBCharacter = OwnerPBCharacter == nullptr ? Cast<APBCharacter>(GetOwner()) : OwnerPBCharacter;
	if (OwnerPBCharacter && bUseServerSideRewind)
	{
		OwnerPBPlayerController = OwnerPBPlayerController == nullptr ? Cast<APBPlayerController>(OwnerPBCharacter->Controller) : OwnerPBPlayerController;
		if (OwnerPBPlayerController && HasAuthority() && OwnerPBPlayerController->HighPingDelegate.IsBound())
		{
			OwnerPBPlayerController->HighPingDelegate.RemoveDynamic(this, &AWeapon::OnPingTooHigh);
		}
	}
}

void AWeapon::SpendRound()
{
	Ammo = FMath::Clamp(Ammo - 1, 0, MagCapacity);
	SetHUDAmmo();

	if (HasAuthority())
	{
		ClientUpdateAmmo(Ammo);
	}
	else
	{
		++Sequence;
	}
}

void AWeapon::ClientUpdateAmmo_Implementation(int32 ServerAmmo)
{
	if (HasAuthority()) return;

	Ammo = ServerAmmo;
	--Sequence;

	Ammo -= Sequence;
	SetHUDAmmo();
}

void AWeapon::AddAmmo(int32 AmmoToAdd)
{
	Ammo = FMath::Clamp(Ammo + AmmoToAdd, 0, MagCapacity);
	SetHUDAmmo();

	ClientAddAmmo(AmmoToAdd);
}

void AWeapon::ClientAddAmmo_Implementation(int32 AmmoToAdd)
{
	if (HasAuthority()) return;

	Ammo = FMath::Clamp(Ammo + AmmoToAdd, 0, MagCapacity);
	
	OwnerPBCharacter = OwnerPBCharacter == nullptr ? Cast<APBCharacter>(GetOwner()) : OwnerPBCharacter;
	if (OwnerPBCharacter && OwnerPBCharacter->GetCombatComponent() && IsFull())
	{
		OwnerPBCharacter->GetCombatComponent()->JumpToShotgunEnd();
	}

	SetHUDAmmo();
}

void AWeapon::SetHUDAmmo()
{
	OwnerPBCharacter = OwnerPBCharacter == nullptr ? Cast<APBCharacter>(GetOwner()) : OwnerPBCharacter;
	if (OwnerPBCharacter)
	{
		OwnerPBPlayerController = OwnerPBPlayerController == nullptr ? Cast<APBPlayerController>(OwnerPBCharacter->Controller) : OwnerPBPlayerController;
		if (OwnerPBPlayerController)
		{
			OwnerPBPlayerController->SetHUDWeaponAmmo(Ammo);
		}
	}
}

void AWeapon::Drop()
{
	SetWeaponState(EWeaponState::EWS_Dropped);

	FDetachmentTransformRules DetachRules(EDetachmentRule::KeepWorld, true);
	WeaponMesh->DetachFromComponent(DetachRules);
	SetOwner(nullptr);
	OwnerPBCharacter = nullptr;
	OwnerPBPlayerController = nullptr;
}

void AWeapon::OnPingTooHigh(bool bPingTooHigh)
{
	bUseServerSideRewind = !bPingTooHigh;
}

bool AWeapon::IsEmpty()
{
	return Ammo <= 0;
}

bool AWeapon::IsFull()
{
	return Ammo == MagCapacity;
}