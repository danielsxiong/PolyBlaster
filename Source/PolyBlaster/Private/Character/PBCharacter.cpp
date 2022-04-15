// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PBCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"

APBCharacter::APBCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

void APBCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void APBCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APBCharacter::Jump);

	PlayerInputComponent->BindAxis("MoveForward", this, &APBCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APBCharacter::MoveRight);
	PlayerInputComponent->BindAxis("TurnMouse", this, &APBCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUpMouse", this, &APBCharacter::LookUp);
	PlayerInputComponent->BindAxis("TurnGamepad", this, &APBCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUpGamepad", this, &APBCharacter::LookUp);
}

void APBCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APBCharacter::MoveForward(float Value)
{
	if (Controller && Value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
		AddMovementInput(Direction, Value);
	}
}

void APBCharacter::MoveRight(float Value)
{
	if (Controller && Value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));
		AddMovementInput(Direction, Value);
	}
}

void APBCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void APBCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}
