// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Menu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void MenuSetup(int32 InNumPublicConnections = 4, FString InMatchType = TEXT("FreeForAll"), FString InPathToLobby = TEXT("/Game/ThirdPerson/Maps/Lobby"));

protected:

	virtual bool Initialize() override;

	void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld);

	// Callbacks
	UFUNCTION()
	virtual void OnCreateSession(bool bWasSuccessful);

	virtual void OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful);

	virtual void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);

	UFUNCTION()
	virtual void OnDestroySession(bool bWasSuccessful);

	UFUNCTION()
	virtual void OnStartSession(bool bWasSuccessful);

private:

	class UMultiplayerSessionsSubsystem* MultiplayerSessionsSubsystem;

	int32 NumPublicConnection{ 4 };

	FString MatchType{ TEXT("FreeForAll") };

	FString PathToLobby{ TEXT("") };

	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;

	UFUNCTION()
	void HostButtonClicked();

	UFUNCTION()
	void JoinButtonClicked();

	void MenuTearDown();
	
};
