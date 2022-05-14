// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PBTypes/TurningInPlace.h"
#include "Interfaces/InteractWithCrosshairsInterface.h"
#include "PBCharacter.generated.h"

UCLASS()
class POLYBLASTER_API APBCharacter : public ACharacter, public IInteractWithCrosshairsInterface
{
	GENERATED_BODY()

public:

	APBCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PostInitializeComponents() override;

	virtual void OnRep_ReplicatedMovement() override;

	void PlayFireMontage(bool bAiming);

	void PlayEliminatedMontage();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastEliminated();

	void Eliminated();

	/*UFUNCTION(NetMulticast, Unreliable)
	void MulticastHit();*/

protected:

	virtual void BeginPlay() override;

	virtual void Jump() override;

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

	void FireButtonPressed();

	void FireButtonReleased();

	void AimOffset(float DeltaTime);

	void CalculateAO_Pitch();

	void SimProxiesTurn();

	void PlayHitReactMontage();

	UFUNCTION()
	void ReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* InstigatorController, AActor* DamageCauser);

	void UpdateHUDHealth();

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

	float AO_Yaw;

	float InterpAO_Yaw;

	float AO_Pitch;

	FRotator StartingAimRotation;

	ETurningInPlace TurningInPlace;

	UPROPERTY(EditAnywhere, Category = Combat)
	class UAnimMontage* FireWeaponMontage;

	UPROPERTY(EditAnywhere, Category = Combat)
	UAnimMontage* HitReactMontage;

	UPROPERTY(EditAnywhere, Category = Combat)
	UAnimMontage* EliminatedMontage;

	UPROPERTY(EditAnywhere)
	float CameraThreshold = 200.f;

	bool bRotateRootBone;

	float TurnThreshold = 0.5f;

	FRotator ProxyRotationLastFrame;

	FRotator ProxyRotation;

	float ProxyYaw;

	float TimeSinceLastMovementReplication;

	void TurnInPlace(float DeltaTime);

	void HideCameraIfCharacterClose();

	UFUNCTION()
	void OnRep_OverlappingWeapon(AWeapon* LastWeapon);

	UFUNCTION(Server, Reliable)
	void ServerEquipButtonPressed();

	float CalculateSpeed();

	/**
	* Player Health
	*/

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float MaxHealth = 100.f;

	UPROPERTY(ReplicatedUsing = OnRep_Health, VisibleAnywhere, Category = "Player Stats")
	float Health = 100.f;

	UFUNCTION()
	void OnRep_Health();

	class APBPlayerController* PBPlayerController;

	/**
	* Player Elimination
	*/

	bool bEliminated = false;

	FTimerHandle EliminatedTimer;

	UPROPERTY(EditDefaultsOnly)
	float EliminatedDelay = 3.f;

	void EliminatedTimerFinished();

public:	

	void SetOverlappingWeapon(AWeapon* InWeapon);

	bool IsWeaponEquipped();

	bool IsAiming();

	AWeapon* GetEquippedWeapon();

	FORCEINLINE float GetAO_Yaw() const { return AO_Yaw; }

	FORCEINLINE float GetAO_Pitch() const { return AO_Pitch; }
	
	FORCEINLINE ETurningInPlace GetTurningInPlace() const { return TurningInPlace; }

	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE bool ShouldRotateRootBone() const { return bRotateRootBone; }

	FORCEINLINE bool IsEliminated() const { return bEliminated; }

	FVector GetHitTarget() const;

};
