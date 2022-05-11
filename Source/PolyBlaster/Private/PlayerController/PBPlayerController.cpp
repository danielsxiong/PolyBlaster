// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/PBPlayerController.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

#include "HUD/PBHUD.h"
#include "HUD/CharacterOverlay.h"

void APBPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PBHUD = Cast<APBHUD>(GetHUD());
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