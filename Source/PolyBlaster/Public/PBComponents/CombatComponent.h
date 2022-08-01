// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "HUD/PBHUD.h"
#include "Weapon/WeaponTypes.h"
#include "PBTypes/CombatState.h"
#include "CombatComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POLYBLASTER_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UCombatComponent();

	friend class APBCharacter;

protected:

	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void FireButtonPressed(bool bPressed);

private:

	class APBCharacter* Character;

	class APBPlayerController* Controller;

	class APBHUD* HUD;

	UPROPERTY(ReplicatedUsing = OnRep_EquippedWeapon)
	class AWeapon* EquippedWeapon;

	UPROPERTY(ReplicatedUsing = OnRep_SecondaryWeapon)
	AWeapon* SecondaryWeapon;

	UPROPERTY(Replicated)
	bool bAiming;

	UPROPERTY(EditAnywhere)
	float BaseWalkSpeed;

	UPROPERTY(EditAnywhere)
	float AimWalkSpeed;

	bool bFireButtonPressed;

	/**
	* HUD and Crosshairs
	*/

	float CrosshairVelocityFactor;

	float CrosshairInAirFactor;

	float CrosshairAimFactor;

	float CrosshairShootingFactor;

	UPROPERTY(Replicated)
	FVector HitTarget;

	FHUDPackage HUDPackage;

	/*
	* Aiming and FOV
	*/

	// Field of view when not aiming, set in the BeginPlay to the camera base FOV
	float DefaultFOV;

	float CurrentFOV;

	UPROPERTY(EditAnywhere, Category = Combat)
	float ZoomedFOV = 30.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float ZoomInterpSpeed = 20.f;

	void InterpFOV(float DeltaTime);

	/*
	* Automatic Fire
	*/

	FTimerHandle FireTimer;

	bool bCanFire = true;

	void StartFireTimer();

	void FireTimerFinished();

	bool CanFire();

	// For currently equipped weapon
	UPROPERTY(ReplicatedUsing = OnRep_CarriedAmmo)
	int32 CarriedAmmo;

	UFUNCTION()
	void OnRep_CarriedAmmo();

	TMap<EWeaponType, int32> CarriedAmmoMap;

	UPROPERTY(EditAnywhere)
	int32 MaxCarriedAmmo = 500;

	UPROPERTY(EditAnywhere)
	int32 StartingARAmmo = 30;

	UPROPERTY(EditAnywhere)
	int32 StartingRocketAmmo = 0;

	UPROPERTY(EditAnywhere)
	int32 StartingPistolAmmo = 16;

	UPROPERTY(EditAnywhere)
	int32 StartingSMGAmmo = 60;

	UPROPERTY(EditAnywhere)
	int32 StartingShotgunAmmo = 12;

	UPROPERTY(EditAnywhere)
	int32 StartingSniperAmmo = 10;

	UPROPERTY(EditAnywhere)
	int32 StartingGrenadeLauncherAmmo = 5;

	void InitializeCarriedAmmo();

	void UpdateHUDCarriedAmmo();

	UPROPERTY(ReplicatedUsing = OnRep_CombatState)
	ECombatState CombatState = ECombatState::ECS_Unoccupied;

	UFUNCTION()
	void OnRep_CombatState();

	UPROPERTY(ReplicatedUsing = OnRep_Grenades)
	int32 Grenades = 4;

	UPROPERTY(EditAnywhere)
	int32 MaxGrenades = 4;

	UFUNCTION()
	void OnRep_Grenades();

	void UpdateHUDGrenades();

protected:

	void SetAiming(bool bIsAiming);

	UFUNCTION(Server, Reliable)
	void ServerSetAiming(bool bIsAiming);

	UFUNCTION()
	void OnRep_EquippedWeapon();

	UFUNCTION()
	void OnRep_SecondaryWeapon();

	void Fire();

	void LocalFire(const FVector_NetQuantize& TraceHitTarget);

	/*
	* Flow on replicating weapon fire
	* 
	* On Server:
	* - Player will call ServerFire() from FireButtonPressed
	* - ServerFire will call MulticastFire() where all the fire effects are being called, MulticastFire will be called on Server and Client
	* 
	* On Client:
	* - Same with server, the difference is that it will let the server run the ServerFire()
	*/
	UFUNCTION(Server, Reliable)
	void ServerFire(const FVector_NetQuantize& TraceHitTarget);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastFire(const FVector_NetQuantize& TraceHitTarget);

	void TraceUnderCrosshairs(FHitResult& TraceHitResult);

	UFUNCTION(Server, Unreliable)
	void ServerSetHitTarget(const FVector_NetQuantize& InHitTarget);

	void SetHUDCrosshairs(float DeltaTime);

	UFUNCTION(Server, Reliable)
	void ServerReload();

	void HandleReload();

	int32 AmountToReload();

	void UpdateAmmoValues();

	void UpdateShotgunAmmoValues();

	void ThrowGrenade();

	void ThrowGrenade_Internal();

	UFUNCTION(Server, Reliable)
	void ServerThrowGrenade();

	void DropEquippedWeapon();

	void AttachActorToRightHand(AActor* ActorToAttach);

	void AttachActorToLeftHand(AActor* ActorToAttach);

	void AttachActorToBackpack(AActor* ActorToAttach);

	void UpdateCarriedAmmo();

	void ReloadEmptyWeapon();

	void PlayEquipWeaponSound(AWeapon* WeaponToEquip);

	void ShowAttachedGrenade(bool bShowGrenade);

	void EquipPrimaryWeapon(AWeapon* WeaponToEquip);

	void EquipSecondaryWeapon(AWeapon* WeaponToEquip);

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> GrenadeClass;

public:

	void EquipWeapon(AWeapon* InWeapon);

	void SwapWeapon();

	void Reload();

	UFUNCTION(BlueprintCallable)
	void FinishReload();

	UFUNCTION(BlueprintCallable)
	void ShotgunShellReload();

	void JumpToShotgunEnd();

	UFUNCTION(BlueprintCallable)
	void ThrowGrenadeFinished();

	UFUNCTION(BlueprintCallable)
	void LaunchGrenade();

	void PickupAmmo(EWeaponType WeaponType, int32 AmmoAmount);

	int32 GetWeaponAmmo() const;

	int32 GetCarriedAmmo() const;

	bool ShouldSwapWeapon();

	FORCEINLINE float GetMaxWalkSpeed() const { return BaseWalkSpeed; }

	FORCEINLINE ECombatState GetCombatState() const { return CombatState; }

	FORCEINLINE void SetCombatState(ECombatState InCombatState) { CombatState = InCombatState; }

	FORCEINLINE int32 GetGrenades() const { return Grenades; }
};
