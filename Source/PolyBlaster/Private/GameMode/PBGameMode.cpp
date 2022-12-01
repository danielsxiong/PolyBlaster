// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/PBGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

#include "Character/PBCharacter.h"
#include "PlayerController/PBPlayerController.h"
#include "PlayerState/PBPlayerState.h"
#include "GameState/PBGameState.h"

namespace MatchState
{
	const FName Cooldown = FName("Cooldown");
}

APBGameMode::APBGameMode()
{
	bDelayedStart = true;
}

void APBGameMode::BeginPlay()
{
	Super::BeginPlay();

	LevelStartingTime = GetWorld()->GetTimeSeconds();
}

void APBGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MatchState == MatchState::WaitingToStart)
	{
		CountdownTime = WarmupTime - GetWorld()->GetTimeSeconds() + LevelStartingTime;

		if (CountdownTime <= 0.f)
		{
			StartMatch();
		}
	}
	else if (MatchState == MatchState::InProgress)
	{
		CountdownTime = WarmupTime + MatchTime - GetWorld()->GetTimeSeconds() + LevelStartingTime;

		if (CountdownTime <= 0.f)
		{
			SetMatchState(MatchState::Cooldown);
		}
	}
	else if (MatchState == MatchState::Cooldown)
	{
		CountdownTime = WarmupTime + MatchTime + CooldownTime - GetWorld()->GetTimeSeconds() + LevelStartingTime;

		if (CountdownTime <= 0.f)
		{
			UWorld* World = GetWorld();
			if (World)
			{
				//bUseSeamlessTravel = true;
				//World->ServerTravel(TEXT("/Game/Maps/PolyBlasterMap?listen"));
				RestartGame();
			}
		}
	}
}

void APBGameMode::OnMatchStateSet()
{
	Super::OnMatchStateSet();

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APBPlayerController* PBPlayerController = Cast<APBPlayerController>(*It);
		if (PBPlayerController)
		{
			PBPlayerController->OnMatchStateSet(MatchState, bTeamsMatch);
		}
	}
}

void APBGameMode::PlayerEliminated(APBCharacter* EliminatedCharacter, APBPlayerController* EliminatedController, APBPlayerController* AttackerController)
{
	APBPlayerState* AttackerPlayerState = AttackerController ? Cast<APBPlayerState>(AttackerController->PlayerState) : nullptr;
	APBPlayerState* VictimPlayerState = EliminatedController ? Cast<APBPlayerState>(EliminatedController->PlayerState) : nullptr;

	APBGameState* PBGameState = GetGameState<APBGameState>();

	if (AttackerPlayerState && AttackerPlayerState != VictimPlayerState && PBGameState)
	{
		TArray<APBPlayerState*> PlayersCurrentlyInTheLead;
		for (auto LeadPlayer : PBGameState->TopScoringPlayers)
		{
			PlayersCurrentlyInTheLead.Add(LeadPlayer);
		}

		AttackerPlayerState->AddToScore(1.f);
		PBGameState->UpdateTopScore(AttackerPlayerState);
		if (PBGameState->TopScoringPlayers.Contains(AttackerPlayerState))
		{
			APBCharacter* Leader = Cast<APBCharacter>(AttackerPlayerState->GetPawn());
			if (Leader)
			{
				Leader->MulticastGainedTheLead();
			}
		}

		for (int32 i = 0; i < PlayersCurrentlyInTheLead.Num(); i++)
		{
			if (!PBGameState->TopScoringPlayers.Contains(PlayersCurrentlyInTheLead[i]))
			{
				APBCharacter* Loser = Cast<APBCharacter>(PlayersCurrentlyInTheLead[i]->GetPawn());
				if (Loser)
				{
					Loser->MulticastLostTheLead();
				}
			}
		}
	}

	if (VictimPlayerState)
	{
		VictimPlayerState->AddToDefeats(1);
	}

	if (EliminatedCharacter)
	{
		EliminatedCharacter->Eliminated();
	}

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APBPlayerController* PBPlayerController = Cast<APBPlayerController>(*It);
		if (PBPlayerController && AttackerPlayerState && VictimPlayerState)
		{
			PBPlayerController->BroadcastElimination(AttackerPlayerState, VictimPlayerState);
		}
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

void APBGameMode::PlayerLeftGame(APBPlayerState* PlayerLeaving)
{
	if (!PlayerLeaving) return;

	APBGameState* PBGameState = GetGameState<APBGameState>();
	if (PBGameState && PBGameState->TopScoringPlayers.Contains(PlayerLeaving))
	{
		PBGameState->TopScoringPlayers.Remove(PlayerLeaving);
	}

	APBCharacter* PBCharacterLeaving = Cast<APBCharacter>(PlayerLeaving->GetPawn());
	if (PBCharacterLeaving)
	{
		PBCharacterLeaving->Eliminated(true);
	}
}

float APBGameMode::CalculateDamage(AController* Attacker, AController* Victim, float BaseDamage)
{
	return BaseDamage;
}
