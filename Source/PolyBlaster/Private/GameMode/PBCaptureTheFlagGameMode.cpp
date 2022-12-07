// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/PBCaptureTheFlagGameMode.h"

#include "Weapon/Flag.h"
#include "CaptureTheFlag/FlagZone.h"
#include "GameState/PBGameState.h"

void APBCaptureTheFlagGameMode::PlayerEliminated(APBCharacter* EliminatedCharacter, APBPlayerController* EliminatedController, APBPlayerController* AttackerController)
{
	APBGameMode::PlayerEliminated(EliminatedCharacter, EliminatedController, AttackerController);
}

void APBCaptureTheFlagGameMode::FlagCaptured(AFlag* Flag, AFlagZone* Zone)
{
	bool bValidCapture = Flag->GetTeam() != Zone->Team;
	APBGameState* PBGameState = Cast<APBGameState>(GameState);
	if (PBGameState)
	{
		if (Zone->Team == ETeam::ET_BlueTeam)
		{
			PBGameState->BlueTeamScores();
		}
		else if (Zone->Team == ETeam::ET_RedTeam)
		{
			PBGameState->RedTeamScores();
		}
	}
}
