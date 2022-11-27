// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/OverheadWidget.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerState.h"

void UOverheadWidget::SetDisplayText(const FString& TextToDisplay)
{
	if (DisplayText)
	{
		DisplayText->SetText(FText::FromString(TextToDisplay));
	}
}

void UOverheadWidget::ShowPlayerNetRole(APawn* InPawn)
{
	ENetRole RemoteRole = InPawn->GetRemoteRole();
	FString Role;

	switch (RemoteRole)
	{
	case ENetRole::ROLE_Authority:
	{
		Role = TEXT("Authority");
		break;
	}
	case ENetRole::ROLE_AutonomousProxy:
	{
		Role = TEXT("AutonomousProxy");
		break;
	}
	case ENetRole::ROLE_SimulatedProxy:
	{
		Role = TEXT("SimulatedProxy");
		break;
	}
	default:
	{
		Role = TEXT("NONE");
		break;
	}
	}

	FString RemoteRoleString = FString::Printf(TEXT("Remote Role: %s"), *Role);
	SetDisplayText(RemoteRoleString);
}

void UOverheadWidget::ShowPlayerName(APawn* InPawn)
{
	APlayerState* PlayerState = InPawn->GetPlayerState();
	if (PlayerState)
	{
		FString PlayerName = PlayerState->GetPlayerName();
		SetDisplayText(PlayerName);
	}
}