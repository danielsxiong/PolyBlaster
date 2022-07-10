// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuffComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POLYBLASTER_API UBuffComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UBuffComponent();

	friend class APBCharacter;

protected:

	virtual void BeginPlay() override;

	void HealRampUp(float DeltaTime);

	void ShieldRampUp(float DeltaTime);

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Heal(float HealAmount, float HealingTime);

	void BuffSpeed(float BuffBaseSpeed, float BuffCrouchSpeed, float SpeedBuffTime);

	void BuffJump(float Velocity, float JumpBuffTime);

	void ReplenishShield(float ShieldAmount, float ReplenishTime);

	void SetInitialSpeeds(float BaseSpeed, float CrouchSpeed);

	void SetInitialJumpVelocity(float Velocity);

private:

	UPROPERTY()
	class APBCharacter* Character;

	/**
	* Health Buff
	*/
	bool bHealing = false;

	float HealingRate = 0.f;

	float AmountToHeal = 0.f;

	/**
	* Speed Buff
	*/
	FTimerHandle SpeedBuffTimer;

	float InitialBaseSpeed;

	float InitialCrouchSpeed;

	void BuffSpeed_Internal(float BaseSpeed, float CrouchSpeed);

	void ResetSpeeds();
	
	UFUNCTION(NetMulticast, Reliable)
	void MulticastSpeedBuff(float BaseSpeed, float CrouchSpeed);

	/**
	* Jump Buff
	*/
	FTimerHandle JumpBuffTimer;

	float InitialJumpVelocity;

	void BuffJump_Internal(float Velocity);

	void ResetJump();
	
	UFUNCTION(NetMulticast, Reliable)
	void MulticastJumpBuff(float Velocity);

	/**
	* Health Buff
	*/
	bool bReplenishShield = false;

	float ShieldReplenishRate = 0.f;

	float AmountToReplenishShield = 0.f;
};
