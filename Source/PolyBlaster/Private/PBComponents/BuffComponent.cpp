// Fill out your copyright notice in the Description page of Project Settings.


#include "PBComponents/BuffComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Character/PBCharacter.h"

UBuffComponent::UBuffComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UBuffComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


void UBuffComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	HealRampUp(DeltaTime);
	ShieldRampUp(DeltaTime);
}

void UBuffComponent::Heal(float HealAmount, float HealingTime)
{
	bHealing = true;
	HealingRate = HealAmount / HealingTime;
	AmountToHeal += HealAmount;
}

void UBuffComponent::HealRampUp(float DeltaTime)
{
	if (!bHealing || !Character || Character->IsEliminated()) return;

	const float HealThisFrame = HealingRate * DeltaTime;
	Character->SetHealth(FMath::Clamp(Character->GetHealth() + HealThisFrame, 0.f, Character->GetMaxHealth()));
	Character->UpdateHUDHealth();
	AmountToHeal -= HealThisFrame;

	if (AmountToHeal <= 0.f || Character->GetHealth() >= Character->GetMaxHealth())
	{
		bHealing = false;
	}
}

void UBuffComponent::SetInitialSpeeds(float BaseSpeed, float CrouchSpeed)
{
	InitialBaseSpeed = BaseSpeed;
	InitialCrouchSpeed = CrouchSpeed;
}

void UBuffComponent::BuffSpeed(float BuffBaseSpeed, float BuffCrouchSpeed, float SpeedBuffTime)
{
	if (!Character) return;

	Character->GetWorldTimerManager().SetTimer(SpeedBuffTimer, this, &UBuffComponent::ResetSpeeds, SpeedBuffTime);

	BuffSpeed_Internal(BuffBaseSpeed, BuffCrouchSpeed);
	MulticastSpeedBuff(BuffBaseSpeed, BuffCrouchSpeed);
}

void UBuffComponent::MulticastSpeedBuff_Implementation(float BaseSpeed, float CrouchSpeed)
{
	BuffSpeed_Internal(BaseSpeed, CrouchSpeed);
}

void UBuffComponent::BuffSpeed_Internal(float BaseSpeed, float CrouchSpeed)
{
	if (Character && Character->GetCharacterMovement())
	{
		Character->GetCharacterMovement()->MaxWalkSpeed = BaseSpeed;
		Character->GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchSpeed;
	}
}

void UBuffComponent::ResetSpeeds()
{
	BuffSpeed_Internal(InitialBaseSpeed, InitialCrouchSpeed);
	MulticastSpeedBuff(InitialBaseSpeed, InitialCrouchSpeed);
}

void UBuffComponent::SetInitialJumpVelocity(float Velocity)
{
	InitialJumpVelocity = Velocity;
}

void UBuffComponent::BuffJump(float Velocity, float JumpBuffTime)
{
	if (!Character) return;

	Character->GetWorldTimerManager().SetTimer(JumpBuffTimer, this, &UBuffComponent::ResetJump, JumpBuffTime);

	BuffJump_Internal(Velocity);
	MulticastJumpBuff(Velocity);
}

void UBuffComponent::MulticastJumpBuff_Implementation(float Velocity)
{
	BuffJump_Internal(Velocity);
}

void UBuffComponent::BuffJump_Internal(float Velocity)
{
	if (Character && Character->GetCharacterMovement())
	{
		Character->GetCharacterMovement()->JumpZVelocity = Velocity;
	}
}

void UBuffComponent::ResetJump()
{
	BuffJump_Internal(InitialJumpVelocity);
	MulticastJumpBuff(InitialJumpVelocity);
}

void UBuffComponent::ReplenishShield(float ShieldAmount, float ReplenishTime)
{
	bReplenishShield = true;
	ShieldReplenishRate = ShieldAmount / ReplenishTime;
	AmountToReplenishShield += ShieldAmount;
}

void UBuffComponent::ShieldRampUp(float DeltaTime)
{
	if (!bReplenishShield || !Character || Character->IsEliminated()) return;

	const float ReplenishThisFrame = ShieldReplenishRate * DeltaTime;
	Character->SetShield(FMath::Clamp(Character->GetShield() + ReplenishThisFrame, 0.f, Character->GetMaxShield()));
	Character->UpdateHUDShield();
	AmountToReplenishShield -= ReplenishThisFrame;

	if (AmountToReplenishShield <= 0.f || Character->GetShield() >= Character->GetMaxShield())
	{
		bReplenishShield = false;
	}
}