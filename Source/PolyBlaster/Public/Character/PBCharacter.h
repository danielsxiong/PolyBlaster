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
	// Sets default values for this character's properties
	APBCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	
	void MoveRight(float Value);

	void Turn(float Value);

	void LookUp(float Value);

private:

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* OverheadWidget;

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

public:	

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void SetOverlappingWeapon(AWeapon* InWeapon);
	
};
