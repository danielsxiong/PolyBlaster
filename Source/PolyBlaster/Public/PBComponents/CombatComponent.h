// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

#define TRACE_LENGTH 10000.f

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

private:

	class APBCharacter* Character;

	class APBPlayerController* Controller;

	class APBHUD* HUD;

	UPROPERTY(ReplicatedUsing = OnRep_EquippedWeapon)
	class AWeapon* EquippedWeapon;

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

protected:

	void SetAiming(bool bIsAiming);

	UFUNCTION(Server, Reliable)
	void ServerSetAiming(bool bIsAiming);

	UFUNCTION()
	void OnRep_EquippedWeapon();

	void FireButtonPressed(bool bPressed);

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

	void SetHUDCrosshairs(float DeltaTime);

public:

	void EquipWeapon(AWeapon* InWeapon);

	FORCEINLINE float GetMaxWalkSpeed() { return BaseWalkSpeed; }
		
};
