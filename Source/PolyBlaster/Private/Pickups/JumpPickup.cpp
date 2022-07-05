// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/JumpPickup.h"

#include "Character/PBCharacter.h"
#include "PBComponents/BuffComponent.h"

AJumpPickup::AJumpPickup()
{
	bReplicates = true;
}

void AJumpPickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweep)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, Sweep);

	APBCharacter* PBCharacter = Cast<APBCharacter>(OtherActor);
	if (PBCharacter)
	{
		UBuffComponent* Buff = PBCharacter->GetBuffComponent();
		if (Buff)
		{
			Buff->BuffJump(JumpZVelocityBuff, JumpBuffTime);
		}
	}

	Destroy();
}