// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PBGameMode.generated.h"

/**
 * 
 */
UCLASS()
class POLYBLASTER_API APBGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	virtual void PlayerEliminated(class APBCharacter* EliminatedCharacter, class APBPlayerController* EliminatedController, APBPlayerController* AttackerController);
};
