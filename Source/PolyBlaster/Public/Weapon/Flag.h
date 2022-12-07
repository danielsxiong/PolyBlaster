// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/Weapon.h"
#include "Flag.generated.h"

/**
 * 
 */
UCLASS()
class POLYBLASTER_API AFlag : public AWeapon
{
	GENERATED_BODY()

public:

	AFlag();

protected:

	virtual void BeginPlay() override;

	virtual void OnEquipped() override;

	virtual void OnDropped() override;

private:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* FlagMesh;

	FTransform InitialTransform;

public:

	virtual void Drop() override;

	void ResetFlag();

	FORCEINLINE FTransform GetInitialLocation() const { return InitialTransform; }
	
};
