// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PBAnimInstance.h"
#include "Character/PBCharacter.h"
#include "Weapon/Weapon.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

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
	Speed = Velocity.Size();

	bIsInAir = PBCharacter->GetCharacterMovement()->IsFalling();

	bIsAccelerating = PBCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;

	bWeaponEquipped = PBCharacter->IsWeaponEquipped();

	EquippedWeapon = PBCharacter->GetEquippedWeapon();

	bIsCrouched = PBCharacter->bIsCrouched;

	bAiming = PBCharacter->IsAiming();

	// Offset Yaw for strafing, this count the delta between movement rotation and aim rotation, then use RInterp to get a smooth yaw offset
	FRotator AimRotation = PBCharacter->GetBaseAimRotation();
	FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(PBCharacter->GetVelocity());
	FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation);
	DeltaRotation = FMath::RInterpTo(DeltaRotation, DeltaRot, DeltaTime, 15.f);
	YawOffset = DeltaRotation.Yaw;

	// Lean, basically this calculates how fast our character is rotating and interpolate them to Lean
	CharacterRotationLastFrame = CharacterRotation;
	CharacterRotation = PBCharacter->GetActorRotation();
	const FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(CharacterRotation, CharacterRotationLastFrame);
	const float Target = Delta.Yaw / DeltaTime;
	const float Interp = FMath::FInterpTo(Lean, Target, DeltaTime, 6.f);
	Lean = FMath::Clamp(Interp, -90.f, 90.f);

	AO_Yaw = PBCharacter->GetAO_Yaw();
	AO_Pitch = PBCharacter->GetAO_Pitch();

	if (bWeaponEquipped && EquippedWeapon && EquippedWeapon->GetWeaponMesh() && PBCharacter->GetMesh())
	{
		LeftHandTransform = EquippedWeapon->GetWeaponMesh()->GetSocketTransform(FName("LeftHandSocket"), ERelativeTransformSpace::RTS_World);

		FVector OutPosition;
		FRotator OutRotation;
		PBCharacter->GetMesh()->TransformToBoneSpace(FName("Hand_R"), LeftHandTransform.GetLocation(), FRotator::ZeroRotator, OutPosition, OutRotation);

		LeftHandTransform.SetLocation(OutPosition);
		LeftHandTransform.SetRotation(FQuat(OutRotation));
	}
}
