// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/PBLobbyGameMode.h"
#include "GameFramework/GameStateBase.h"

void APBLobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	int32 NumOfPlayers = GameState.Get()->PlayerArray.Num();
	if (NumOfPlayers == 2)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			bUseSeamlessTravel = true;
			World->ServerTravel(TEXT("/Game/Maps/PolyBlasterMap?listen"));
		}
	}
}