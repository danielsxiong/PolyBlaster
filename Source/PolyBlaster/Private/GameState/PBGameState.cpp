// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/PBGameState.h"
#include "Net/UnrealNetwork.h"

#include "PlayerState/PBPlayerState.h"
#include "PlayerController/PBPlayerController.h"

void APBGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APBGameState, TopScoringPlayers);
	DOREPLIFETIME(APBGameState, RedTeamScore);
	DOREPLIFETIME(APBGameState, BlueTeamScore);
}

void APBGameState::UpdateTopScore(APBPlayerState* ScoringPlayer)
{
	if (TopScoringPlayers.Num() == 0)
	{
		TopScoringPlayers.AddUnique(ScoringPlayer);
		TopScore = ScoringPlayer->GetScore();
	}
	else if (ScoringPlayer->GetScore() == TopScore)
	{
		TopScoringPlayers.AddUnique(ScoringPlayer);
	}
	else if (ScoringPlayer->GetScore() > TopScore)
	{
		TopScoringPlayers.Empty();
		TopScoringPlayers.AddUnique(ScoringPlayer);
		TopScore = ScoringPlayer->GetScore();
	}
}

void APBGameState::OnRep_RedTeamScore()
{
	APBPlayerController* PBPlayerController = Cast<APBPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PBPlayerController)
	{
		PBPlayerController->SetHUDRedTeamScore(RedTeamScore);
	}
}

void APBGameState::OnRep_BlueTeamScore()
{
	APBPlayerController* PBPlayerController = Cast<APBPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PBPlayerController)
	{
		PBPlayerController->SetHUDBlueTeamScore(BlueTeamScore);
	}
}

void APBGameState::RedTeamScores()
{
	++RedTeamScore;

	APBPlayerController* PBPlayerController = Cast<APBPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PBPlayerController)
	{
		PBPlayerController->SetHUDRedTeamScore(RedTeamScore);
	}
}

void APBGameState::BlueTeamScores()
{
	++BlueTeamScore;

	APBPlayerController* PBPlayerController = Cast<APBPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PBPlayerController)
	{
		PBPlayerController->SetHUDBlueTeamScore(BlueTeamScore);
	}
}
