// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/PBTeamsGameMode.h"
#include "PBCaptureTheFlagGameMode.generated.h"

/**
 * 
 */
UCLASS()
class POLYBLASTER_API APBCaptureTheFlagGameMode : public APBTeamsGameMode
{
	GENERATED_BODY()

public:

	virtual void PlayerEliminated(class APBCharacter* EliminatedCharacter, class APBPlayerController* EliminatedController, APBPlayerController* AttackerController) override;

	void FlagCaptured(class AFlag* Flag, class AFlagZone* Zone);
	
};
