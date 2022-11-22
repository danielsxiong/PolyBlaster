// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/EliminatedAnnouncement.h"
#include "Components/TextBlock.h"

void UEliminatedAnnouncement::SetEliminatedAnnouncementText(const FString& AttackerName, const FString& VictimName)
{
	FString EliminatedAnnouncementText = FString::Printf(TEXT("%s eliminated %s"), *AttackerName, *VictimName);
	if (AnnouncementText)
	{
		AnnouncementText->SetText(FText::FromString(EliminatedAnnouncementText));
	}
}