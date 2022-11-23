// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/PBHUD.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/HorizontalBox.h"
#include "Components/CanvasPanelSlot.h"

#include "HUD/CharacterOverlay.h"
#include "HUD/Announcement.h"
#include "HUD/EliminatedAnnouncement.h"

void APBHUD::BeginPlay()
{
	Super::BeginPlay();
}

void APBHUD::AddCharacterOverlay()
{
	OwningPlayerController = OwningPlayerController == nullptr ? GetOwningPlayerController() : OwningPlayerController;
	if (OwningPlayerController && CharacterOverlayClass)
	{
		CharacterOverlay = CreateWidget<UCharacterOverlay>(OwningPlayerController, CharacterOverlayClass);
		if (CharacterOverlay)
		{
			CharacterOverlay->AddToViewport();
		}
	}
}

void APBHUD::AddAnnouncement()
{
	OwningPlayerController = OwningPlayerController == nullptr ? GetOwningPlayerController() : OwningPlayerController;
	if (OwningPlayerController && AnnouncementClass)
	{
		Announcement = CreateWidget<UAnnouncement>(OwningPlayerController, AnnouncementClass);
		if (Announcement)
		{
			Announcement->AddToViewport();
		}
	}
}

void APBHUD::AddEliminatedAnnouncement(const FString& Attacker, const FString& Victim)
{
	OwningPlayerController = OwningPlayerController == nullptr ? GetOwningPlayerController() : OwningPlayerController;
	if (OwningPlayerController && EliminatedAnnouncementClass)
	{
		UEliminatedAnnouncement* EliminatedAnnouncement = CreateWidget<UEliminatedAnnouncement>(OwningPlayerController, EliminatedAnnouncementClass);
		if (EliminatedAnnouncement)
		{
			EliminatedAnnouncement->SetEliminatedAnnouncementText(Attacker, Victim);
			EliminatedAnnouncement->AddToViewport();

			for (UEliminatedAnnouncement* Message : EliminatedMessages)
			{
				if (Message && Message->AnnouncementBox)
				{
					UCanvasPanelSlot* CanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(Message->AnnouncementBox);
					if (CanvasSlot)
					{
						FVector2D Position = CanvasSlot->GetPosition();
						FVector2D NewPosition(Position.X, Position.Y - CanvasSlot->GetSize().Y);

						CanvasSlot->SetPosition(NewPosition);
					}
				}
			}

			EliminatedMessages.Add(EliminatedAnnouncement);

			FTimerHandle EliminatedMessageTimer;
			FTimerDelegate EliminatedMessageDelegate;

			EliminatedMessageDelegate.BindUFunction(this, FName("EliminatedAnnouncementTimerFinished"), EliminatedAnnouncement);
			GetWorldTimerManager().SetTimer(EliminatedMessageTimer, EliminatedMessageDelegate, EliminatedAnnouncementTime, false /*not looping*/);
		}
	}
}

void APBHUD::EliminatedAnnouncementTimerFinished(UEliminatedAnnouncement* MessageToRemove)
{
	if (MessageToRemove)
	{
		MessageToRemove->RemoveFromParent();
	}
}

void APBHUD::DrawHUD()
{
	Super::DrawHUD();

	FVector2D ViewportSize;
	if (GEngine)
	{
		GEngine->GameViewport->GetViewportSize(ViewportSize);
		
		const FVector2D ViewportCenter(ViewportSize.X / 2.f, ViewportSize.Y / 2.f);

		float SpreadScaled = CrosshairSpreadMax * HUDPackage.CrosshairSpread;

		if (HUDPackage.CrosshairsCenter)
		{
			FVector2D Spread(0.f, 0.f);
			DrawCrosshair(HUDPackage.CrosshairsCenter, ViewportCenter, Spread, HUDPackage.CrosshairColor);
		}
		if (HUDPackage.CrosshairsLeft)
		{
			FVector2D Spread(-SpreadScaled, 0.f);
			DrawCrosshair(HUDPackage.CrosshairsLeft, ViewportCenter, Spread, HUDPackage.CrosshairColor);
		}
		if (HUDPackage.CrosshairsRight)
		{
			FVector2D Spread(SpreadScaled, 0.f);
			DrawCrosshair(HUDPackage.CrosshairsRight, ViewportCenter, Spread, HUDPackage.CrosshairColor);
		}
		if (HUDPackage.CrosshairsTop)
		{
			FVector2D Spread(0.f, -SpreadScaled);
			DrawCrosshair(HUDPackage.CrosshairsTop, ViewportCenter, Spread, HUDPackage.CrosshairColor);
		}
		if (HUDPackage.CrosshairsBottom)
		{
			FVector2D Spread(0.f, SpreadScaled);
			DrawCrosshair(HUDPackage.CrosshairsBottom, ViewportCenter, Spread, HUDPackage.CrosshairColor);
		}
	}
}

void APBHUD::DrawCrosshair(UTexture2D* Texture, FVector2D ViewportCenter, FVector2D Spread, FLinearColor CrosshairColor)
{
	if (!Texture) return;

	const float TextureWidth = Texture->GetSizeX();
	const float TextureHeight = Texture->GetSizeY();
	const FVector2D TextureDrawPoint(
		ViewportCenter.X - (TextureWidth / 2.f) + Spread.X,
		ViewportCenter.Y - (TextureHeight / 2.f) + Spread.Y
	);

	DrawTexture(Texture, TextureDrawPoint.X, TextureDrawPoint.Y, TextureWidth, TextureHeight, 0.f, 0.f, 1.f, 1.f, CrosshairColor);
}