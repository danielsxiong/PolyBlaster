// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GrenadeMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class POLYBLASTER_API UGrenadeMovementComponent : public UProjectileMovementComponent
{
	GENERATED_BODY()

protected:

	virtual EHandleBlockingHitResult HandleBlockingHit(const FHitResult& Hit, float TimeTick, const FVector& MoveDelta, float& SubTickTimeRemaining) override;
};
