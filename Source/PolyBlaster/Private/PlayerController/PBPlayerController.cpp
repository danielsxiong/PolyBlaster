// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/PBPlayerController.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

#include "HUD/PBHUD.h"
#include "HUD/CharacterOverlay.h"
#include "Character/PBCharacter.h"
#include "PlayerState/PBPlayerState.h"

void APBPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PBHUD = Cast<APBHUD>(GetHUD());
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

void APBPlayerController::SetHUDHealth(float Health, float MaxHealth)
{
	if (!PBHUD)
	{
		PBHUD = Cast<APBHUD>(GetHUD());
	}

	bool bHUDValid = PBHUD && PBHUD->CharacterOverlay && PBHUD->CharacterOverlay->HealthBar && PBHUD->CharacterOverlay->HealthText;
	if (bHUDValid)
	{
		const float HealthPercent = Health / MaxHealth;
		PBHUD->CharacterOverlay->HealthBar->SetPercent(HealthPercent);
		FString HealthText = FString::Printf(TEXT("%d/%d"), FMath::CeilToInt(Health), FMath::CeilToInt(MaxHealth));
		PBHUD->CharacterOverlay->HealthText->SetText(FText::FromString(HealthText));
	}
}

void APBPlayerController::SetHUDScore(float Score)
{
	if (!PBHUD)
	{
		PBHUD = Cast<APBHUD>(GetHUD());
	}

	bool bHUDValid = PBHUD && PBHUD->CharacterOverlay && PBHUD->CharacterOverlay->ScoreAmount;
	if (bHUDValid)
	{
		FString ScoreText = FString::Printf(TEXT("%d"), FMath::FloorToInt(Score));
		PBHUD->CharacterOverlay->ScoreAmount->SetText(FText::FromString(ScoreText));
	}
}

void APBPlayerController::SetHUDDefeats(int32 Defeats)
{
	if (!PBHUD)
	{
		PBHUD = Cast<APBHUD>(GetHUD());
	}

	bool bHUDValid = PBHUD && PBHUD->CharacterOverlay && PBHUD->CharacterOverlay->DefeatsAmount;
	if (bHUDValid)
	{
		FString DefeatsText = FString::Printf(TEXT("%d"), Defeats);
		PBHUD->CharacterOverlay->DefeatsAmount->SetText(FText::FromString(DefeatsText));
	}
}

void APBPlayerController::SetHUDWeaponAmmo(int32 Ammo)
{
	if (!PBHUD)
	{
		PBHUD = Cast<APBHUD>(GetHUD());
	}

	bool bHUDValid = PBHUD && PBHUD->CharacterOverlay && PBHUD->CharacterOverlay->WeaponAmmoAmmount;
	if (bHUDValid)
	{
		FString AmmoText = FString::Printf(TEXT("%d"), Ammo);
		PBHUD->CharacterOverlay->WeaponAmmoAmmount->SetText(FText::FromString(AmmoText));
	}
}

void APBPlayerController::SetHUDCarriedAmmo(int32 Ammo)
{
	if (!PBHUD)
	{
		PBHUD = Cast<APBHUD>(GetHUD());
	}

	bool bHUDValid = PBHUD && PBHUD->CharacterOverlay && PBHUD->CharacterOverlay->CarriedAmmoAmmount;
	if (bHUDValid)
	{
		FString AmmoText = FString::Printf(TEXT("%d"), Ammo);
		PBHUD->CharacterOverlay->CarriedAmmoAmmount->SetText(FText::FromString(AmmoText));
	}
}

void APBPlayerController::SetHUDMatchCountdown(float CountdownTime)
{
	if (!PBHUD)
	{
		PBHUD = Cast<APBHUD>(GetHUD());
	}

	bool bHUDValid = PBHUD && PBHUD->CharacterOverlay && PBHUD->CharacterOverlay->MatchCountdownText;
	if (bHUDValid)
	{
		int32 Minutes = FMath::FloorToInt(CountdownTime / 60.f);
		int32 Seconds = CountdownTime - (Minutes * 60);
		FString CountdownText = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
		PBHUD->CharacterOverlay->MatchCountdownText->SetText(FText::FromString(CountdownText));
	}
}

void APBPlayerController::SetHUDTime()
{
	uint32 SecondsLeft = FMath::CeilToInt(MatchTime - GetServerTime());

	if (CountdownInt != SecondsLeft)
	{
		SetHUDMatchCountdown(MatchTime - GetServerTime());
	}

	CountdownInt = SecondsLeft;
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
