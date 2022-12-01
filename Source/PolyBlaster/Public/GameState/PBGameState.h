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

	/**
	* Teams
	*/

	TArray<APBPlayerState*> RedTeam;

	TArray<APBPlayerState*> BlueTeam;

	UPROPERTY(ReplicatedUsing = OnRep_RedTeamScore)
	float RedTeamScore = 0.f;

	UFUNCTION()
	void OnRep_RedTeamScore();

	UPROPERTY(ReplicatedUsing = OnRep_BlueTeamScore)
	float BlueTeamScore = 0.f;

	UFUNCTION()
	void OnRep_BlueTeamScore();

	void RedTeamScores();

	void BlueTeamScores();

private:

	float TopScore = 0.f;
};
