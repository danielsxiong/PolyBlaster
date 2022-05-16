// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PBPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class POLYBLASTER_API APBPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	virtual void OnPossess(APawn* InPawn) override;

	void SetHUDHealth(float Health, float MaxHealth);

	void SetHUDScore(float Score);

protected:

	virtual void BeginPlay() override;

private:
	
	class APBHUD* PBHUD;
};
