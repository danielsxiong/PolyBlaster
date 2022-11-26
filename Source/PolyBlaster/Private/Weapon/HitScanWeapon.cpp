// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/HitScanWeapon.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"
#include "DrawDebugHelpers.h"

#include "Character/PBCharacter.h"
#include "PlayerController/PBPlayerController.h"
#include "Weapon/WeaponTypes.h"
#include "PBComponents/LagCompensationComponent.h"

void AHitScanWeapon::Fire(const FVector& HitTarget)
{
	Super::Fire(HitTarget);

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn)
	{
		return;
	}

	AController* InstigatorController = OwnerPawn->GetController();

	const USkeletalMeshSocket* MuzzleFlashSocket = GetWeaponMesh()->GetSocketByName("MuzzleFlash");
	if (MuzzleFlashSocket)
	{
		FTransform SocketTransform = MuzzleFlashSocket->GetSocketTransform(GetWeaponMesh());
		FVector Start = SocketTransform.GetLocation();

		FHitResult FireHit;
		WeaponTraceHit(Start, HitTarget, FireHit);

		UWorld* World = GetWorld();
		if (World)
		{
			if (FireHit.bBlockingHit)
			{
				APBCharacter* PBCharacter = Cast<APBCharacter>(FireHit.GetActor());
				if (PBCharacter && InstigatorController)
				{
					bool bCauseAuthDamage = !bUseServerSideRewind || OwnerPawn->IsLocallyControlled();
					if (HasAuthority() && bCauseAuthDamage)
					{
						const float DamageToCause = FireHit.BoneName.ToString() == FString("head") ? HeadShotDamage : Damage;
						UGameplayStatics::ApplyDamage(PBCharacter, DamageToCause, InstigatorController, this, UDamageType::StaticClass());
					}
					else if (!HasAuthority() && bUseServerSideRewind)
					{
						OwnerPBCharacter = OwnerPBCharacter == nullptr ? Cast<APBCharacter>(OwnerPawn) : OwnerPBCharacter;
						OwnerPBPlayerController = OwnerPBPlayerController == nullptr ? Cast<APBPlayerController>(InstigatorController) : OwnerPBPlayerController;

						if (OwnerPBPlayerController && OwnerPBCharacter && OwnerPBCharacter->GetLagCompensationComponent() && OwnerPBCharacter->IsLocallyControlled())
						{
							OwnerPBCharacter->GetLagCompensationComponent()->ServerScoreRequest(PBCharacter, Start, FireHit.ImpactPoint, OwnerPBPlayerController->GetServerTime() - OwnerPBPlayerController->SingleTripTime);
						}
					}
				}

				if (ImpactParticles)
				{
					UGameplayStatics::SpawnEmitterAtLocation(World, ImpactParticles, FireHit.ImpactPoint, FireHit.ImpactNormal.Rotation());
				}

				if (HitSound)
				{
					UGameplayStatics::PlaySoundAtLocation(this, HitSound, FireHit.ImpactPoint);
				}
			}

			if (MuzzleFlash)
			{
				UGameplayStatics::SpawnEmitterAtLocation(World, MuzzleFlash, SocketTransform);
			}

			if (FireSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}
		}
	}
}

void AHitScanWeapon::WeaponTraceHit(const FVector& TraceStart, const FVector& HitTarget, FHitResult& OutHit)
{
	UWorld* World = GetWorld();
	if (World)
	{
		FVector End = TraceStart + (HitTarget - TraceStart) * 1.25f;
		World->LineTraceSingleByChannel(OutHit, TraceStart, End, ECollisionChannel::ECC_Visibility);
		
		FVector BeamEnd = End;

		if (OutHit.bBlockingHit)
		{
			BeamEnd = OutHit.ImpactPoint;
		}
		else
		{
			OutHit.ImpactPoint = End;
		}

		// DrawDebugSphere(GetWorld(), BeamEnd, 16.f, 12, FColor::Orange, true);

		if (BeamParticles)
		{
			UParticleSystemComponent* Beam = UGameplayStatics::SpawnEmitterAtLocation(World, BeamParticles, TraceStart, FRotator::ZeroRotator, true);
			if (Beam)
			{
				Beam->SetVectorParameter(FName("Target"), BeamEnd);
			}
		}
	}
}