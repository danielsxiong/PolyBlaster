// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PBAnimInstance.h"
#include "Character/PBCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPBAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	PBCharacter = Cast<APBCharacter>(TryGetPawnOwner());
}

void UPBAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (!PBCharacter)
	{
		PBCharacter = Cast<APBCharacter>(TryGetPawnOwner());
	}

	if (!PBCharacter)
	{
		return;
	}

	FVector Velocity = PBCharacter->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Length();

	bIsInAir = PBCharacter->GetCharacterMovement()->IsFalling();

	bIsAccelerating = PBCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;
}
