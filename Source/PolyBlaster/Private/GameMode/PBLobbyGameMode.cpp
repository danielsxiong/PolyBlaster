// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/PBLobbyGameMode.h"
#include "GameFramework/GameStateBase.h"

#include "MultiplayerSessionsSubsystem.h"

void APBLobbyGameMode::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle LobbyTimeoutHandle;
	GetWorldTimerManager().SetTimer(LobbyTimeoutHandle, this, &APBLobbyGameMode::FinishLobbyTimeout, LobbyTimeout);
}

void APBLobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	int32 NumOfPlayers = GameState.Get()->PlayerArray.Num();
	int32 DesiredNumPlayers = 2; // Default 2

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		UMultiplayerSessionsSubsystem* Subsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
		if (Subsystem)
		{
			DesiredNumPlayers = Subsystem->DesiredNumPublicConnections;
		}
	}

	if (NumOfPlayers == DesiredNumPlayers)
	{
		TravelToGame();
	}
}

void APBLobbyGameMode::TravelToGame()
{
	FString MatchType = "FreeForAll"; // Default FreeForAll

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		UMultiplayerSessionsSubsystem* Subsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
		if (Subsystem)
		{
			MatchType = Subsystem->DesiredMatchType;
		}
	}

	UWorld* World = GetWorld();
	if (World)
	{
		// bUseSeamlessTravel = true;
		if (MatchType == "FreeForAll")
		{
			World->ServerTravel(TEXT("/Game/Maps/PolyBlasterMap?listen"));
		}
		else if (MatchType == "Teams")
		{
			World->ServerTravel(TEXT("/Game/Maps/TeamsMap?listen"));
		}
		else if (MatchType == "CaptureTheFlag")
		{
			World->ServerTravel(TEXT("/Game/Maps/CaptureTheFlagMap?listen"));
		}
	}
}


void APBLobbyGameMode::FinishLobbyTimeout()
{
	TravelToGame();
}
