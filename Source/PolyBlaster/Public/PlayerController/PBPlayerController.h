// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PBPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHighPingDelegate, bool, bPingTooHigh);

/**
 * 
 */
UCLASS()
class POLYBLASTER_API APBPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaTime) override;

	// Sync with server time as soon as possible
	virtual void ReceivedPlayer() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Sync with server world time
	virtual float GetServerTime();

	void OnMatchStateSet(FName State, bool bTeamsMatch = false);

	void SetHUDHealth(float Health, float MaxHealth);

	void SetHUDShield(float Shield, float MaxShield);

	void SetHUDScore(float Score);

	void SetHUDDefeats(int32 Defeats);

	void SetHUDWeaponAmmo(int32 Ammo);

	void SetHUDCarriedAmmo(int32 Ammo);

	void SetHUDMatchCountdown(float CountdownTime);

	void SetHUDAnnouncementCountdown(float CountdownTime);

	void SetHUDGrenade(int32 Grenades);

	void HideTeamScores();

	void InitTeamScores();

	void SetHUDRedTeamScore(int32 RedScore);

	void SetHUDBlueTeamScore(int32 BlueScore);

	float SingleTripTime = 0.f;

	FHighPingDelegate HighPingDelegate;

	void BroadcastElimination(APlayerState* Attacker, APlayerState* Victim);

protected:

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	void SetHUDTime();

	void PollInit();

	void HandleMatchHasStarted(bool bTeamsMatch = false);

	void HandleCooldown();

	UFUNCTION(Server, Reliable)
	void ServerCheckMatchState();

	UFUNCTION(Client, Reliable)
	void ClientJoinMidgame(FName InMatchState, float InWarmupTime, float InMatchTime, float InCooldownTime, float InLevelStartingTime);

	/**
	* Sync time between client and server
	*/

	// Client will request server time using this function, passing in the client's current time when the request was sent
	UFUNCTION(Server, Reliable)
	void ServerRequestServerTime(float TimeOfClientRequest);

	// Server will return server time using this function, passing in the client's current time when the request was sent and the time when server received the request
	UFUNCTION(Client, Reliable)
	void ClientReportServerTime(float TimeOfClientRequest, float TimeServerReceivedRequest);

	void CheckTimeSync(float DeltaTime);

	// Difference between client and server time
	float ClientServerDelta = 0.f;

	UPROPERTY(EditAnywhere, Category = Time)
	float TimeSyncFrequency = 5.f;

	float TimeSyncRunningTime = 0.f;

	/**
	* High Ping
	*/

	void HighPingWarning();

	void StopHighPingWarning();

	void CheckPing(float DeltaTime);

	/**
	* Exit
	*/

	void ShowReturnToMainMenu();

	UFUNCTION(Client, Reliable)
	void ClientEliminationAnnouncement(APlayerState* Attacker, APlayerState* Victim);

	/**
	* Teams
	*/

	UPROPERTY(ReplicatedUsing = OnRep_ShowTeamScores)
	bool bShowTeamScores = false;

	UFUNCTION()
	void OnRep_ShowTeamScores();

private:
	
	UPROPERTY()
	class APBHUD* PBHUD;

	UPROPERTY()
	class APBGameMode* PBGameMode;

	UPROPERTY()
	class UCharacterOverlay* CharacterOverlay;

	UPROPERTY(EditAnywhere, Category = HUD)
	TSubclassOf<class UUserWidget> ReturnToMainMenuWidget;

	UPROPERTY()
	class UReturnToMainMenu* ReturnToMainMenu;

	bool bReturnToMainMenuOpen = false;

	float LevelStartingTime = 0.f;

	float MatchTime = 0.f;

	float WarmupTime = 0.f;

	float CooldownTime = 0.f;

	uint32 CountdownInt = 0;

	float HUDHealth;

	bool bInitializeHealth = false;

	float HUDMaxHealth;

	float HUDShield;

	bool bInitializeShield = false;

	float HUDMaxShield;

	float HUDScore;

	bool bInitializeScore = false;

	int32 HUDDefeats;

	bool bInitializeDefeats = false;

	int32 HUDGrenades;

	bool bInitializeGrenades = false;

	int32 HUDCarriedAmmo;

	bool bInitializeCarriedAmmo = false;

	int32 HUDWeaponAmmo;

	bool bInitializeWeaponAmmo = false;

	UPROPERTY(ReplicatedUsing = OnRep_MatchState)
	FName MatchState;

	UFUNCTION()
	void OnRep_MatchState();

	float HighPingRunningTime = 0.f;

	UPROPERTY(EditAnywhere)
	float HighPingDuration = 5.f;

	float PingAnimationRunningTime = 0.f;

	UPROPERTY(EditAnywhere)
	float CheckPingFrequency = 20.f;

	UPROPERTY(EditAnywhere)
	float HighPingThreshold = 50.f;

	UFUNCTION(Server, Reliable)
	void ServerReportPingStatus(bool bHighPing);
};
