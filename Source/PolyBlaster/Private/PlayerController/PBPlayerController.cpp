// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/PBPlayerController.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"

#include "HUD/PBHUD.h"
#include "HUD/CharacterOverlay.h"
#include "HUD/Announcement.h"
#include "Character/PBCharacter.h"
#include "PlayerState/PBPlayerState.h"
#include "GameMode/PBGameMode.h"

void APBPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PBHUD = Cast<APBHUD>(GetHUD());

	ServerCheckMatchState();
}

void APBPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APBPlayerController, MatchState);
}

void APBPlayerController::ReceivedPlayer()
{
	Super::ReceivedPlayer();
	if (IsLocalController())
	{
		ServerRequestServerTime(GetWorld()->GetTimeSeconds());
	}
}

void APBPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetHUDTime();

	CheckTimeSync(DeltaTime);

	PollInit();
}

void APBPlayerController::PollInit()
{
	if (!CharacterOverlay)
	{
		if (PBHUD && PBHUD->CharacterOverlay)
		{
			CharacterOverlay = PBHUD->CharacterOverlay;

			if (CharacterOverlay)
			{
				SetHUDHealth(HUDHealth, HUDMaxHealth);
				SetHUDScore(HUDScore);
				SetHUDDefeats(HUDDefeats);
			}
		}
	}
}

void APBPlayerController::CheckTimeSync(float DeltaTime)
{
	TimeSyncRunningTime += DeltaTime;
	if (IsLocalController() && TimeSyncRunningTime > TimeSyncFrequency)
	{
		ServerRequestServerTime(GetWorld()->GetTimeSeconds());
		TimeSyncRunningTime = 0.f;
	}
}

float APBPlayerController::GetServerTime()
{
	if (HasAuthority())
	{
		return GetWorld()->GetTimeSeconds();
	}

	// If it's client
	return GetWorld()->GetTimeSeconds() + ClientServerDelta;
}

void APBPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	APBCharacter* PBCharacter = Cast<APBCharacter>(InPawn);
	if (PBCharacter)
	{
		SetHUDHealth(PBCharacter->GetHealth(), PBCharacter->GetMaxHealth());
	}
}

void APBPlayerController::OnMatchStateSet(FName State)
{
	MatchState = State;

	if (MatchState == MatchState::InProgress)
	{
		HandleMatchHasStarted();
	}
}

void APBPlayerController::OnRep_MatchState()
{
	if (MatchState == MatchState::InProgress)
	{
		HandleMatchHasStarted();
	}
}

void APBPlayerController::HandleMatchHasStarted()
{
	PBHUD = PBHUD == nullptr ? Cast<APBHUD>(GetHUD()) : PBHUD;
	if (PBHUD)
	{
		if (PBHUD->Announcement)
		{
			PBHUD->Announcement->SetVisibility(ESlateVisibility::Hidden);
		}
		PBHUD->AddCharacterOverlay();
	}
}

void APBPlayerController::SetHUDHealth(float Health, float MaxHealth)
{
	PBHUD = PBHUD == nullptr ? Cast<APBHUD>(GetHUD()) : PBHUD;

	bool bHUDValid = PBHUD && PBHUD->CharacterOverlay && PBHUD->CharacterOverlay->HealthBar && PBHUD->CharacterOverlay->HealthText;
	if (bHUDValid)
	{
		const float HealthPercent = Health / MaxHealth;
		PBHUD->CharacterOverlay->HealthBar->SetPercent(HealthPercent);
		FString HealthText = FString::Printf(TEXT("%d/%d"), FMath::CeilToInt(Health), FMath::CeilToInt(MaxHealth));
		PBHUD->CharacterOverlay->HealthText->SetText(FText::FromString(HealthText));
	}
	else
	{
		bInitializeCharacterOverlay = true;

		HUDHealth = Health;
		HUDMaxHealth = MaxHealth;
	}
}

void APBPlayerController::SetHUDScore(float Score)
{
	PBHUD = PBHUD == nullptr ? Cast<APBHUD>(GetHUD()) : PBHUD;

	bool bHUDValid = PBHUD && PBHUD->CharacterOverlay && PBHUD->CharacterOverlay->ScoreAmount;
	if (bHUDValid)
	{
		FString ScoreText = FString::Printf(TEXT("%d"), FMath::FloorToInt(Score));
		PBHUD->CharacterOverlay->ScoreAmount->SetText(FText::FromString(ScoreText));
	}
	else
	{
		bInitializeCharacterOverlay = true;

		HUDScore = Score;
	}
}

void APBPlayerController::SetHUDDefeats(int32 Defeats)
{
	PBHUD = PBHUD == nullptr ? Cast<APBHUD>(GetHUD()) : PBHUD;

	bool bHUDValid = PBHUD && PBHUD->CharacterOverlay && PBHUD->CharacterOverlay->DefeatsAmount;
	if (bHUDValid)
	{
		FString DefeatsText = FString::Printf(TEXT("%d"), Defeats);
		PBHUD->CharacterOverlay->DefeatsAmount->SetText(FText::FromString(DefeatsText));
	}
	else
	{
		bInitializeCharacterOverlay = true;

		HUDDefeats = Defeats;
	}
}

void APBPlayerController::SetHUDWeaponAmmo(int32 Ammo)
{
	PBHUD = PBHUD == nullptr ? Cast<APBHUD>(GetHUD()) : PBHUD;

	bool bHUDValid = PBHUD && PBHUD->CharacterOverlay && PBHUD->CharacterOverlay->WeaponAmmoAmmount;
	if (bHUDValid)
	{
		FString AmmoText = FString::Printf(TEXT("%d"), Ammo);
		PBHUD->CharacterOverlay->WeaponAmmoAmmount->SetText(FText::FromString(AmmoText));
	}
}

void APBPlayerController::SetHUDCarriedAmmo(int32 Ammo)
{
	PBHUD = PBHUD == nullptr ? Cast<APBHUD>(GetHUD()) : PBHUD;

	bool bHUDValid = PBHUD && PBHUD->CharacterOverlay && PBHUD->CharacterOverlay->CarriedAmmoAmmount;
	if (bHUDValid)
	{
		FString AmmoText = FString::Printf(TEXT("%d"), Ammo);
		PBHUD->CharacterOverlay->CarriedAmmoAmmount->SetText(FText::FromString(AmmoText));
	}
}

void APBPlayerController::SetHUDMatchCountdown(float CountdownTime)
{
	PBHUD = PBHUD == nullptr ? Cast<APBHUD>(GetHUD()) : PBHUD;

	bool bHUDValid = PBHUD && PBHUD->CharacterOverlay && PBHUD->CharacterOverlay->MatchCountdownText;
	if (bHUDValid)
	{
		int32 Minutes = FMath::FloorToInt(CountdownTime / 60.f);
		int32 Seconds = CountdownTime - (Minutes * 60);
		FString CountdownText = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
		PBHUD->CharacterOverlay->MatchCountdownText->SetText(FText::FromString(CountdownText));
	}
}

void APBPlayerController::SetHUDAnnouncementCountdown(float CountdownTime)
{
	PBHUD = PBHUD == nullptr ? Cast<APBHUD>(GetHUD()) : PBHUD;

	bool bHUDValid = PBHUD && PBHUD->Announcement && PBHUD->Announcement->WarmupTime;
	if (bHUDValid)
	{
		int32 Minutes = FMath::FloorToInt(CountdownTime / 60.f);
		int32 Seconds = CountdownTime - (Minutes * 60);
		FString CountdownText = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
		PBHUD->Announcement->WarmupTime->SetText(FText::FromString(CountdownText));
	}
}

void APBPlayerController::SetHUDTime()
{
	float TimeLeft = 0.f;
	if (MatchState == MatchState::WaitingToStart)
	{
		TimeLeft = WarmupTime - GetServerTime() + LevelStartingTime;
	}
	else if (MatchState == MatchState::InProgress)
	{
		TimeLeft = WarmupTime + MatchTime - GetServerTime() + LevelStartingTime;
	}

	uint32 SecondsLeft = FMath::CeilToInt(TimeLeft - GetServerTime());

	if (CountdownInt != SecondsLeft)
	{
		if (MatchState == MatchState::WaitingToStart)
		{
			SetHUDAnnouncementCountdown(TimeLeft);
		}
		if (MatchState == MatchState::InProgress)
		{
			SetHUDMatchCountdown(TimeLeft);
		}
	}

	CountdownInt = SecondsLeft;
}

void APBPlayerController::ServerCheckMatchState_Implementation()
{
	APBGameMode* GameMode = Cast<APBGameMode>(UGameplayStatics::GetGameMode(this));
	if (GameMode)
	{
		WarmupTime = GameMode->WarmupTime;
		MatchTime = GameMode->MatchTime;
		LevelStartingTime = GameMode->LevelStartingTime;
		MatchState = GameMode->GetMatchState();

		ClientJoinMidgame(MatchState, WarmupTime, MatchTime, LevelStartingTime);

		if (PBHUD && MatchState == MatchState::WaitingToStart)
		{
			PBHUD->AddAnnouncement();
		}
	}
}

void APBPlayerController::ClientJoinMidgame_Implementation(FName InMatchState, float InWarmupTime, float InMatchTime, float InLevelStartingTime)
{
	WarmupTime = InWarmupTime;
	MatchTime = InMatchTime;
	LevelStartingTime = InLevelStartingTime;
	MatchState = InMatchState;

	OnMatchStateSet(MatchState);

	if (PBHUD && MatchState == MatchState::WaitingToStart)
	{
		PBHUD->AddAnnouncement();
	}
}

void APBPlayerController::ServerRequestServerTime_Implementation(float TimeOfClientRequest)
{
	float ServerTimeOfReceipt = GetWorld()->GetTimeSeconds();
	ClientReportServerTime(TimeOfClientRequest, ServerTimeOfReceipt);
}

void APBPlayerController::ClientReportServerTime_Implementation(float TimeOfClientRequest, float TimeServerReceivedRequest)
{
	float RoundTripTime = GetWorld()->GetTimeSeconds() - TimeOfClientRequest;
	float CurrentServerTime = TimeServerReceivedRequest + (0.5f * RoundTripTime);
	ClientServerDelta = CurrentServerTime - GetWorld()->GetTimeSeconds();
}
