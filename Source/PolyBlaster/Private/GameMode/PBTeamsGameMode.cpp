// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/PBTeamsGameMode.h"
#include "Kismet/GameplayStatics.h"

#include "GameState/PBGameState.h"
#include "PlayerState/PBPlayerState.h"

void APBTeamsGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	APBGameState* PBGameState = Cast<APBGameState>(UGameplayStatics::GetGameState(this));
	if (PBGameState)
	{
		APBPlayerState* PBPlayerState = NewPlayer->GetPlayerState<APBPlayerState>();
		if (PBPlayerState && PBPlayerState->GetTeam() == ETeam::ET_NoTeam)
		{
			if (PBGameState->BlueTeam.Num() >= PBGameState->RedTeam.Num())
			{
				PBGameState->RedTeam.AddUnique(PBPlayerState);
				PBPlayerState->SetTeam(ETeam::ET_RedTeam);
			}
			else
			{
				PBGameState->BlueTeam.AddUnique(PBPlayerState);
				PBPlayerState->SetTeam(ETeam::ET_BlueTeam);
			}
		}
	}
}

void APBTeamsGameMode::Logout(AController* Exiting)
{
	APBGameState* PBGameState = Cast<APBGameState>(UGameplayStatics::GetGameState(this));
	APBPlayerState* PBPlayerState = Exiting->GetPlayerState<APBPlayerState>();

	if (PBGameState && PBPlayerState)
	{
		if (PBGameState->RedTeam.Contains(PBPlayerState))
		{
			PBGameState->RedTeam.Remove(PBPlayerState);
		}
		if (PBGameState->BlueTeam.Contains(PBPlayerState))
		{
			PBGameState->BlueTeam.Remove(PBPlayerState);
		}
	}
}

void APBTeamsGameMode::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();

	APBGameState* PBGameState = Cast<APBGameState>(UGameplayStatics::GetGameState(this));
	if (PBGameState)
	{
		for (auto PlayerState : PBGameState->PlayerArray)
		{
			APBPlayerState* PBPlayerState = Cast<APBPlayerState>(PlayerState.Get());
			if (PBPlayerState && PBPlayerState->GetTeam() == ETeam::ET_NoTeam)
			{
				if (PBGameState->BlueTeam.Num() >= PBGameState->RedTeam.Num())
				{
					PBGameState->RedTeam.AddUnique(PBPlayerState);
					PBPlayerState->SetTeam(ETeam::ET_RedTeam);
				}
				else
				{
					PBGameState->BlueTeam.AddUnique(PBPlayerState);
					PBPlayerState->SetTeam(ETeam::ET_BlueTeam);
				}
			}
		}
	}
}