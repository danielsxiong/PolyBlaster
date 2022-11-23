// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PBHUD.generated.h"

USTRUCT(BlueprintType)
struct FHUDPackage
{
	GENERATED_BODY()

public:

	class UTexture2D* CrosshairsCenter;

	UTexture2D* CrosshairsLeft;

	UTexture2D* CrosshairsRight;

	UTexture2D* CrosshairsTop;

	UTexture2D* CrosshairsBottom;

	float CrosshairSpread;

	FLinearColor CrosshairColor;

};

/**
 * 
 */
UCLASS()
class POLYBLASTER_API APBHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	void AddCharacterOverlay();

	void AddAnnouncement();

	void AddEliminatedAnnouncement(const FString& Attacker, const FString& Victim);

	virtual void DrawHUD() override;

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	TSubclassOf<class UUserWidget> CharacterOverlayClass;

	UPROPERTY()
	class UCharacterOverlay* CharacterOverlay;

	UPROPERTY(EditAnywhere, Category = "Announcement")
	TSubclassOf<class UUserWidget> AnnouncementClass;

	UPROPERTY()
	class UAnnouncement* Announcement;

protected:

	virtual void BeginPlay() override;

private:

	class APlayerController* OwningPlayerController;

	UPROPERTY()
	FHUDPackage HUDPackage;

	UPROPERTY(EditAnywhere)
	float CrosshairSpreadMax = 16.f;

	void DrawCrosshair(UTexture2D* Texture, FVector2D ViewportCenter, FVector2D Spread, FLinearColor CrosshairColor);

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> EliminatedAnnouncementClass;

	UPROPERTY()
	TArray<UEliminatedAnnouncement*> EliminatedMessages;

	UPROPERTY(EditAnywhere)
	float EliminatedAnnouncementTime = 2.5f;

	UFUNCTION()
	void EliminatedAnnouncementTimerFinished(UEliminatedAnnouncement* MessageToRemove);

public:

	FORCEINLINE void SetHUDPackage(const FHUDPackage& InPackage) { HUDPackage = InPackage; }

};
