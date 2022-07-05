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

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Heal(float HealAmount, float HealingTime);

	void BuffSpeed(float BuffBaseSpeed, float BuffCrouchSpeed, float SpeedBuffTime);

	void SetInitialSpeeds(float BaseSpeed, float CrouchSpeed);

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
};
