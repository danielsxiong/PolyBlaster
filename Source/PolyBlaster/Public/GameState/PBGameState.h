// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "PBGameState.generated.h"

/**
 * 
 */
UCLASS()
class POLYBLASTER_API APBGameState : public AGameState
{
	GENERATED_BODY()
	
public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void UpdateTopScore(class APBPlayerState* ScoringPlayer);

	UPROPERTY(Replicated)
	TArray<APBPlayerState*> TopScoringPlayers;

private:

	float TopScore = 0.f;
};
