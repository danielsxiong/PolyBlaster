// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"

#include "PBTypes/TurningInPlace.h"
#include "Interfaces/InteractWithCrosshairsInterface.h"
#include "PBTypes/CombatState.h"
#include "PBTypes/Team.h"
#include "PBCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLeftGame);

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

	virtual void Destroyed() override;

	/**
	* Play Montages
	*/

	void PlayFireMontage(bool bAiming);

	void PlayEliminatedMontage();

	void PlayReloadMontage();

	void PlayThrowGrenadeMontage();

	void PlaySwapMontage();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastEliminated(bool bPlayerLeftGame = false);

	void Eliminated(bool bPlayerLeftGame = false);

	UFUNCTION(BlueprintImplementableEvent)
	void ShowSniperScopeWidget(bool bShowScope);

	void UpdateHUDHealth();

	void UpdateHUDShield();

	void UpdateHUDAmmo();

	UFUNCTION(Server, Reliable)
	void ServerLeaveGame();

	FOnLeftGame OnLeftGame;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastGainedTheLead();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastLostTheLead();

	/*UFUNCTION(NetMulticast, Unreliable)
	void MulticastHit();*/

	void SetTeamColor(ETeam Team);

	UPROPERTY(Replicated)
	bool bDisableGameplay = false;

	bool bFinishedSwapping = false;

	UPROPERTY()
	TMap<FName, class UBoxComponent*> HitCollisionBoxes;

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

	void ReloadButtonPressed();

	void ThrowGrenadeButtonPressed();

	void AimOffset(float DeltaTime);

	void CalculateAO_Pitch();

	void SimProxiesTurn();

	void RotateInPlace(float DeltaTime);

	void PlayHitReactMontage();

	UFUNCTION()
	void ReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* InstigatorController, AActor* DamageCauser);

	// Poll for any relevant classes and init HUD
	void PollInit();

	void DropOrDestroyWeapon(AWeapon* Weapon);

	/**
	* Hit boxes used for server side rewind
	*/

	UPROPERTY(EditAnywhere)
	class UBoxComponent* HeadBox;

	UPROPERTY(EditAnywhere)
	UBoxComponent* PelvisBox;

	UPROPERTY(EditAnywhere)
	UBoxComponent* Spine02Box;

	UPROPERTY(EditAnywhere)
	UBoxComponent* Spine03Box;

	UPROPERTY(EditAnywhere)
	UBoxComponent* UpperArm_LBox;

	UPROPERTY(EditAnywhere)
	UBoxComponent* UpperArm_RBox;

	UPROPERTY(EditAnywhere)
	UBoxComponent* LowerArm_LBox;

	UPROPERTY(EditAnywhere)
	UBoxComponent* LowerArm_RBox;

	UPROPERTY(EditAnywhere)
	UBoxComponent* Hand_LBox;

	UPROPERTY(EditAnywhere)
	UBoxComponent* Hand_RBox;

	UPROPERTY(EditAnywhere)
	UBoxComponent* Thigh_LBox;

	UPROPERTY(EditAnywhere)
	UBoxComponent* Thigh_RBox;

	UPROPERTY(EditAnywhere)
	UBoxComponent* Calf_LBox;

	UPROPERTY(EditAnywhere)
	UBoxComponent* Calf_RBox;

	UPROPERTY(EditAnywhere)
	UBoxComponent* Foot_LBox;

	UPROPERTY(EditAnywhere)
	UBoxComponent* Foot_RBox;

private:

	UPROPERTY()
	class APBGameMode* PBGameMode;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* OverheadWidget;

	/**
	* PB Components
	*/

	// bIsReplicated - true
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCombatComponent* Combat;

	// bIsReplicated - true
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBuffComponent* Buff;

	UPROPERTY(VisibleAnywhere)
	class ULagCompensationComponent* LagCompensation;

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

	UPROPERTY(EditAnywhere, Category = Combat)
	UAnimMontage* ReloadMontage;

	UPROPERTY(EditAnywhere, Category = Combat)
	UAnimMontage* ThrowGrenadeMontage;

	UPROPERTY(EditAnywhere, Category = Combat)
	UAnimMontage* SwapMontage;

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

	UPROPERTY()
	class APBPlayerController* PBPlayerController;

	/**
	* Player Health
	*/

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float MaxHealth = 100.f;

	UPROPERTY(ReplicatedUsing = OnRep_Health, VisibleAnywhere, Category = "Player Stats")
	float Health = 100.f;

	UFUNCTION()
	void OnRep_Health(float LastHealth);

	/**
	* Player Shield
	*/

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float MaxShield = 100.f;

	UPROPERTY(ReplicatedUsing = OnRep_Shield, EditAnywhere, Category = "Player Stats")
	float Shield = 100.f;

	UFUNCTION()
	void OnRep_Shield(float LastShield);

	/**
	* Player Elimination
	*/

	bool bEliminated = false;

	bool bLeftGame = false;

	FTimerHandle EliminatedTimer;

	FTimerHandle DisableCollisionTimer;

	UPROPERTY(EditDefaultsOnly)
	float EliminatedDelay = 3.f;

	UPROPERTY(EditDefaultsOnly)
	float DisableCollisionDelay = 0.5f;

	void EliminatedTimerFinished();

	void DisableCollisionTimerFinished();

	/**
	* Player Dissolve Effect
	*/

	UPROPERTY(VisibleAnywhere)
	UTimelineComponent* DissolveTimeline;

	FOnTimelineFloat DissolveTrack;

	UPROPERTY(EditAnywhere);
	UCurveFloat* DissolveCurve;

	// Dynamic Instance to change at runtime
	UPROPERTY(VisibleAnywhere, Category = Eliminated)
	UMaterialInstanceDynamic* DynamicDissolveMaterialInstance;

	// Material Instance set on the BP, used with Dynamic Material Instance
	UPROPERTY(VisibleAnywhere, Category = Eliminated)
	UMaterialInstance* DissolveMaterialInstance;

	UFUNCTION()
	void UpdateDissolveMaterial(float DissolveValue);

	void StartDissolve();

	/**
	* Team colors
	*/

	UPROPERTY(EditAnywhere, Category = Eliminated)
	UMaterialInstance* RedDissolveMaterialInstance;

	UPROPERTY(EditAnywhere, Category = Eliminated)
	UMaterialInstance* RedMaterial;

	UPROPERTY(EditAnywhere, Category = Eliminated)
	UMaterialInstance* BlueDissolveMaterialInstance;

	UPROPERTY(EditAnywhere, Category = Eliminated)
	UMaterialInstance* BlueMaterial;

	UPROPERTY(EditAnywhere, Category = Eliminated)
	UMaterialInstance* OriginalMaterial;

	/**
	* Elimination Effects
	*/

	UPROPERTY(EditAnywhere);
	UParticleSystem* ElimBotEffect;

	UPROPERTY(VisibleAnywhere);
	UParticleSystemComponent* ElimBotComponent;

	UPROPERTY(EditAnywhere);
	class USoundCue* ElimBotSound;

	UPROPERTY()
	class APBPlayerState* PBPlayerState;

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* CrownSystem;

	UPROPERTY()
	class UNiagaraComponent* CrownComponent;

	/**
	* Grenade
	*/

	UPROPERTY(VisibleAnywhere);
	UStaticMeshComponent* AttachedGrenade;

	/**
	* Default Weapon
	*/

	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> DefaultWeaponClass;

public:	

	void SpawnDefaultWeapon();

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

	FORCEINLINE float GetHealth() const { return Health; }

	FORCEINLINE void SetHealth(float Amount) { Health = Amount; }

	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

	FORCEINLINE float GetShield() const { return Shield; }

	FORCEINLINE void SetShield(float Amount) { Shield = Amount; }

	FORCEINLINE float GetMaxShield() const { return MaxShield; }

	FORCEINLINE UCombatComponent* GetCombatComponent() const { return Combat; }

	FORCEINLINE UAnimMontage* GetReloadMontage() const { return ReloadMontage; }

	FORCEINLINE UStaticMeshComponent* GetAttachedGrenade() const { return AttachedGrenade; }

	FORCEINLINE UBuffComponent* GetBuffComponent() const { return Buff; }

	FORCEINLINE ULagCompensationComponent* GetLagCompensationComponent() const { return LagCompensation; }

	bool IsLocallyReloading() const;

	FVector GetHitTarget() const;

	ECombatState GetCombatState() const;

};
