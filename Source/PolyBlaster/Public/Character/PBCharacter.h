// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PBCharacter.generated.h"

UCLASS()
class POLYBLASTER_API APBCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	APBCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PostInitializeComponents() override;

protected:

	virtual void BeginPlay() override;

	void MoveForward(float Value);
	
	void MoveRight(float Value);

	void Turn(float Value);

	void LookUp(float Value);

	/*
	* Flow for equipping weapon
	*
	* On Server:
	* - Player on server will call EquipButtonPressed as usual, then call Combat->EquipWeapon()
	* - Server will receive call ServerEquipButtonPressed() from client, and will call Combat->EquipWeapon() for the player that calls the function
	*
	* On Client:
	* - Player on client doesn't have the authority, so it will call ServerEquipButtonPressed() to request the server for equipping the weapon
	* - Player will receive the replicated Combat component that already have the equipped weapon from the server
	*
	*/
	void EquipButtonPressed();

	void CrouchButtonPressed();

	void AimButtonPressed();

	void AimButtonReleased();

private:

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* OverheadWidget;

	// bIsReplicated - true
	UPROPERTY(VisibleAnywhere)
	class UCombatComponent* Combat;

	/*
	* Flow for replicating OverlappingWeapon
	*
	* On Server:
	* - AWeapon only have collision and overlap enabled on server, so the server will set OverlappingWeapon to the respective player that overlaps with it
	* - If Player is locally controlled on server, ShowPickupWeapon(false) to hide the widget before setting the overlapping weapon (to handle end overlap)
	* - if OverlappingWeapon is not null, ShowPickupWeapon(true) (to handle begin overlap)
	*
	* On Client:
	* - Player On client will receive OnRep_OverlappingWeapon from server, which will call ShowPickupWeapon(true) if OverlappingWeapon is not null (handle begin overlap)
	* - if OverlappingWeapon is null, use value from LastWeapon to call ShowPickupWeapon(false) (handle end overlap)
	*
	*/
	UPROPERTY(ReplicatedUsing = OnRep_OverlappingWeapon)
	class AWeapon* OverlappingWeapon;

	UFUNCTION()
	void OnRep_OverlappingWeapon(AWeapon* LastWeapon);

	UFUNCTION(Server, Reliable)
	void ServerEquipButtonPressed();

public:	

	void SetOverlappingWeapon(AWeapon* InWeapon);

	bool IsWeaponEquipped();

	bool IsAiming();
	
};
