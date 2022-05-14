// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/PBGameMode.h"
#include "Character/PBCharacter.h"
#include "PlayerController/PBPlayerController.h"

void APBGameMode::PlayerEliminated(APBCharacter* EliminatedCharacter, APBPlayerController* EliminatedController, APBPlayerController* AttackerController)
{
	if (EliminatedCharacter)
	{
		EliminatedCharacter->MulticastEliminated();
	}
}