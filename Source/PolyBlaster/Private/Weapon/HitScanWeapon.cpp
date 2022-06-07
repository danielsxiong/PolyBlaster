// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/HitScanWeapon.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"

#include "Character/PBCharacter.h"

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
	if (MuzzleFlashSocket && InstigatorController)
	{
		FTransform SocketTransform = MuzzleFlashSocket->GetSocketTransform(GetWeaponMesh());
		FVector Start = SocketTransform.GetLocation();
		FVector End = Start + (HitTarget - Start) * 1.25f;

		FHitResult FireHit;
		UWorld* World = GetWorld();
		if (World)
		{
			World->LineTraceSingleByChannel(FireHit, Start, End, ECollisionChannel::ECC_Visibility);

			if (FireHit.bBlockingHit)
			{
				APBCharacter* PBCharacter = Cast<APBCharacter>(FireHit.GetActor());
				if (PBCharacter)
				{
					if (HasAuthority())
					{
						UGameplayStatics::ApplyDamage(PBCharacter, Damage, InstigatorController, this, UDamageType::StaticClass());
					}
				}

				if (ImpactParticles)
				{
					UGameplayStatics::SpawnEmitterAtLocation(World, ImpactParticles, HitTarget, FireHit.ImpactNormal.Rotation());
				}
			}
		}
	}
}