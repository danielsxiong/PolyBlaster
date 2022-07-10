// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupSpawnPoint.generated.h"

UCLASS()
class POLYBLASTER_API APickupSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	

	APickupSpawnPoint();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class APickup>> PickupClasses;

	UPROPERTY()
	APickup* SpawnedPickup;

	void SpawnPickup();

	UFUNCTION()
	void SpawnPickupTimerFinished();

	UFUNCTION()
	void StartSpawnPickupTimer(AActor* DestroyedActor);

private:

	FTimerHandle SpawnPickupTimer;

	UPROPERTY(EditAnywhere)
	float SpawnPickupTimeMin;

	UPROPERTY(EditAnywhere)
	float SpawnPickupTimeMax;

};
