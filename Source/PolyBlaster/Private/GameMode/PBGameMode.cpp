// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/PBGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

#include "Character/PBCharacter.h"
#include "PlayerController/PBPlayerController.h"
#include "PlayerState/PBPlayerState.h"

void APBGameMode::PlayerEliminated(APBCharacter* EliminatedCharacter, APBPlayerController* EliminatedController, APBPlayerController* AttackerController)
{
	APBPlayerState* AttackerPlayerState = AttackerController ? Cast<APBPlayerState>(AttackerController->PlayerState) : nullptr;
	APBPlayerState* VictimPlayerState = EliminatedController ? Cast<APBPlayerState>(EliminatedController->PlayerState) : nullptr;

	if (AttackerPlayerState && AttackerPlayerState != VictimPlayerState)
	{
		AttackerPlayerState->AddToScore(1.f);
	}

	if (EliminatedCharacter)
	{
		EliminatedCharacter->Eliminated();
	}
}

void APBGameMode::RequestRespawn(class ACharacter* EliminatedCharacter, AController* EliminatedController)
{
	if (EliminatedCharacter)
	{
		EliminatedCharacter->Reset();
		//EliminatedCharacter->Destroy();
	}

	if (EliminatedController)
	{
		TArray<AActor*> PlayerStarts;
		UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), PlayerStarts);

		int32 Selection = FMath::RandRange(0, PlayerStarts.Num() - 1);
		RestartPlayerAtPlayerStart(EliminatedController, PlayerStarts[Selection]);
	}
}