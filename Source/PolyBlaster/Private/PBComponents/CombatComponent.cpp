// Fill out your copyright notice in the Description page of Project Settings.


#include "PBComponents/CombatComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Weapon/Weapon.h"
#include "Character/PBCharacter.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCombatComponent::EquipWeapon(AWeapon* InWeapon)
{
	if (!Character || !InWeapon)
	{
		return;
	}

	EquippedWeapon = InWeapon;
	EquippedWeapon->SetWeaponState(EWeaponState::EWS_Equipped);

	const USkeletalMeshSocket* HandSocket = Character->GetMesh()->GetSocketByName(FName("RightHandSocket"));
	if (HandSocket)
	{
		HandSocket->AttachActor(EquippedWeapon, Character->GetMesh());
	}

	EquippedWeapon->SetOwner(Character);
	EquippedWeapon->ShowPickupWidget(false);
}