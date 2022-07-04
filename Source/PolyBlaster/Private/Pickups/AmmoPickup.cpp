// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/AmmoPickup.h"
#include "Character/PBCharacter.h"
#include "PBComponents/CombatComponent.h"

void AAmmoPickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweep)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, Sweep);

	APBCharacter* PBCharacter = Cast<APBCharacter>(OtherActor);
	if (PBCharacter)
	{
		UCombatComponent* Combat = PBCharacter->GetCombatComponent();
		if (Combat)
		{
			Combat->PickupAmmo(WeaponType, AmmoAmount);
		}
	}

	Destroy();
}