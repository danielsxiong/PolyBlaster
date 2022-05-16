// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerState/PBPlayerState.h"

#include "Character/PBCharacter.h"
#include "PlayerController/PBPlayerController.h"

void APBPlayerState::AddToScore(float ScoreAmount)
{
	Score += ScoreAmount;

	Character = Character == nullptr ? Cast<APBCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<APBPlayerController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHUDScore(Score);
		}
	}
}

void APBPlayerState::OnRep_Score()
{
	Super::OnRep_Score();

	Character = Character == nullptr ? Cast<APBCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<APBPlayerController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHUDScore(Score);
		}
	}
}