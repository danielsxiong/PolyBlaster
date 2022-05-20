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

	APBGameMode();

	virtual void Tick(float DeltaTime) override;

	virtual void PlayerEliminated(class APBCharacter* EliminatedCharacter, class APBPlayerController* EliminatedController, APBPlayerController* AttackerController);

	virtual void RequestRespawn(class ACharacter* EliminatedCharacter, AController* EliminatedController);

	UPROPERTY(EditDefaultsOnly)
	float WarmupTime = 10.f;

	float LevelStartingTime = 0.f;

protected:

	virtual void BeginPlay();

private:

	float CountdownTime = 0.f;
};
