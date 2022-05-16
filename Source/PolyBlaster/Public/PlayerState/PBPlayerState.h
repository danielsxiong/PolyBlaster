// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PBPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class POLYBLASTER_API APBPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:

	virtual void OnRep_Score() override;

	void AddToScore(float ScoreAmount);

private:

	class APBCharacter* Character;

	class APBPlayerController* Controller;
};
