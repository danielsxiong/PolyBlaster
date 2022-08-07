// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/HitScanWeapon.h"
#include "Shotgun.generated.h"

/**
 * 
 */
UCLASS()
class POLYBLASTER_API AShotgun : public AHitScanWeapon
{
	GENERATED_BODY()

public:

	virtual void Fire(const FVector& HitTarget) override;

	void ShotgunTraceEndWithScatter(const FVector& HitTarget, TArray<FVector>& OutHitTargets);

private:

	UPROPERTY(EditAnywhere, Category = "Weapon Scatter")
	uint32 NumPellets = 12;
	
};
