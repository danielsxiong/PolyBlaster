// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/PBGameMode.h"
#include "PBTeamsGameMode.generated.h"

/**
 * 
 */
UCLASS()
class POLYBLASTER_API APBTeamsGameMode : public APBGameMode
{
	GENERATED_BODY()

	APBTeamsGameMode();

public:

	// For players joining mid game
	virtual void PostLogin(APlayerController* NewPlayer) override;

	// For players leaving mid game
	virtual void Logout(AController* Exiting) override;

	virtual void PlayerEliminated(class APBCharacter* EliminatedCharacter, class APBPlayerController* EliminatedController, APBPlayerController* AttackerController) override;

	virtual float CalculateDamage(AController* Attacker, AController* Victim, float BaseDamage) override;

protected:

	virtual void HandleMatchHasStarted() override;
	
};
