// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PBPlayerController.generated.h"

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

	// Sync with server world time
	virtual float GetServerTime();

	void SetHUDHealth(float Health, float MaxHealth);

	void SetHUDScore(float Score);

	void SetHUDDefeats(int32 Defeats);

	void SetHUDWeaponAmmo(int32 Ammo);

	void SetHUDCarriedAmmo(int32 Ammo);

	void SetHUDMatchCountdown(float CountdownTime);

protected:

	virtual void BeginPlay() override;

	void SetHUDTime();

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

private:
	
	UPROPERTY()
	class APBHUD* PBHUD;

	float MatchTime = 120.f;

	uint32 CountdownInt = 0;
};
