// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PBGameMode.generated.h"

namespace MatchState
{
	// Match duration is over, display winner and begin cooldown timer
	extern POLYBLASTER_API const FName Cooldown;
}

/**
 * 
 */
UCLASS()
class POLYBLASTER_API APBGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	APBGameMode();

	virtual void Tick(float DeltaTime) override;

	virtual void PlayerEliminated(class APBCharacter* EliminatedCharacter, class APBPlayerController* EliminatedController, APBPlayerController* AttackerController);

	virtual void RequestRespawn(class ACharacter* EliminatedCharacter, AController* EliminatedController);

	void PlayerLeftGame(class APBPlayerState* PlayerLeaving);

	virtual float CalculateDamage(AController* Attacker, AController* Victim, float BaseDamage);

	UPROPERTY(EditDefaultsOnly)
	float WarmupTime = 10.f;

	UPROPERTY(EditDefaultsOnly)
	float MatchTime = 120.f;

	UPROPERTY(EditDefaultsOnly)
	float CooldownTime = 10.f;

	float LevelStartingTime = 0.f;

protected:

	virtual void BeginPlay();

	virtual void OnMatchStateSet() override;

private:

	float CountdownTime = 0.f;

public:

	FORCEINLINE float GetCountdownTime() { return CountdownTime; }
};
