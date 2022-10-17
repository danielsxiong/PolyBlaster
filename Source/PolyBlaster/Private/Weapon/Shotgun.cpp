// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Shotgun.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"

#include "Character/PBCharacter.h"
#include "PlayerController/PBPlayerController.h"
#include "PBComponents/LagCompensationComponent.h"

void AShotgun::FireShotgun(const TArray<FVector_NetQuantize>& HitTargets)
{
	AWeapon::Fire(FVector());

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return;

	AController* InstigatorController = OwnerPawn->GetController();

	const USkeletalMeshSocket* MuzzleFlashSocket = GetWeaponMesh()->GetSocketByName("MuzzleFlash");
	if (MuzzleFlashSocket)
	{
		const FTransform SocketTransform = MuzzleFlashSocket->GetSocketTransform(GetWeaponMesh());
		const FVector Start = SocketTransform.GetLocation();

		// Maps hit character to a number of times hit
		TMap<APBCharacter*, uint32> HitMap;

		for (FVector_NetQuantize HitTarget : HitTargets)
		{
			FHitResult FireHit;
			WeaponTraceHit(Start, HitTarget, FireHit);

			APBCharacter* PBCharacter = Cast<APBCharacter>(FireHit.GetActor());
			if (PBCharacter)
			{
				if (HitMap.Contains(PBCharacter))
				{
					HitMap[PBCharacter]++;
				}
				else
				{
					HitMap.Emplace(PBCharacter, 1);
				}
			}

			if (ImpactParticles)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticles, FireHit.ImpactPoint, FireHit.ImpactNormal.Rotation());
			}

			if (HitSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, HitSound, FireHit.ImpactPoint, 1.f, FMath::FRandRange(-1.f, 1.f));
			}
		}

		TArray<APBCharacter*> HitCharacters;

		for (auto HitPair : HitMap)
		{
			if (HitPair.Key && InstigatorController)
			{
				if (HasAuthority() && !bUseServerSideRewind)
				{
					UGameplayStatics::ApplyDamage(HitPair.Key, Damage * HitPair.Value, InstigatorController, this, UDamageType::StaticClass());
				}
				
				HitCharacters.Add(HitPair.Key);
			}
		}

	if (!HasAuthority() && bUseServerSideRewind)
	{
		OwnerPBCharacter = OwnerPBCharacter == nullptr ? Cast<APBCharacter>(OwnerPawn) : OwnerPBCharacter;
		OwnerPBPlayerController = OwnerPBPlayerController == nullptr ? Cast<APBPlayerController>(InstigatorController) : OwnerPBPlayerController;

		if (OwnerPBPlayerController && OwnerPBCharacter && OwnerPBCharacter->GetLagCompensationComponent() && OwnerPBCharacter->IsLocallyControlled())
		{
			OwnerPBCharacter->GetLagCompensationComponent()->ShotgunServerScoreRequest(HitCharacters, Start, HitTargets, OwnerPBPlayerController->GetServerTime() - OwnerPBPlayerController->SingleTripTime, this);
		}
	}
	}
}

void AShotgun::ShotgunTraceEndWithScatter(const FVector& HitTarget, TArray<FVector_NetQuantize>& OutHitTargets)
{
	const USkeletalMeshSocket* MuzzleFlashSocket = GetWeaponMesh()->GetSocketByName("MuzzleFlash");
	if (!MuzzleFlashSocket) return;

	const FTransform SocketTransform = MuzzleFlashSocket->GetSocketTransform(GetWeaponMesh());
	const FVector TraceStart = SocketTransform.GetLocation();

	const FVector ToTargetNormalized = (HitTarget - TraceStart).GetSafeNormal();
	const FVector SphereCenter = TraceStart + ToTargetNormalized * DistanceToSphere;

	for (uint32 i = 0; i < NumPellets; i++)
	{
		const FVector RandVec = UKismetMathLibrary::RandomUnitVector() * FMath::FRandRange(0.f, SphereRadius);
		const FVector EndLoc = SphereCenter + RandVec;
		const FVector ToEndLoc = EndLoc - TraceStart;
		const FVector ResultTarget = FVector(TraceStart + ToEndLoc * TRACE_LENGTH / ToEndLoc.Size());

		OutHitTargets.Add(ResultTarget);
	}
}