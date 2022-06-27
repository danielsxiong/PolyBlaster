// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/GrenadeMovementComponent.h"

UGrenadeMovementComponent::EHandleBlockingHitResult UGrenadeMovementComponent::HandleBlockingHit(const FHitResult& Hit, float TimeTick, const FVector& MoveDelta, float& SubTickTimeRemaining)
{
	Super::HandleBlockingHit(Hit, TimeTick, MoveDelta, SubTickTimeRemaining);

	if (Hit.GetActor() == GetOwner())
	{
		return EHandleBlockingHitResult::AdvanceNextSubstep;
	}

	return EHandleBlockingHitResult::Deflect;
}