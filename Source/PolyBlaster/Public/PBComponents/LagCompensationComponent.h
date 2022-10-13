// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LagCompensationComponent.generated.h"

USTRUCT(BlueprintType)
struct FBoxInformation
{
	GENERATED_BODY()

	UPROPERTY()
	FVector Location;

	UPROPERTY();
	FRotator Rotation;

	UPROPERTY()
	FVector BoxExtent;
};

USTRUCT(BlueprintType)
struct FFramePackage
{
	GENERATED_BODY()

	UPROPERTY()
	float Time;

	UPROPERTY()
	TMap<FName, FBoxInformation> HitBoxInfo;

	UPROPERTY()
	class APBCharacter* Character;
};

USTRUCT(BlueprintType)
struct FServerSideRewindResult
{
	GENERATED_BODY()

	UPROPERTY()
	bool bHitConfirmed;

	UPROPERTY()
	bool bHeadShot;
};

USTRUCT(BlueprintType)
struct FShotgunServerSideRewindResult
{
	GENERATED_BODY()

	UPROPERTY()
	TMap<class APBCharacter*, uint32> HeadShots;

	UPROPERTY()
	TMap<APBCharacter*, uint32> BodyShots;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POLYBLASTER_API ULagCompensationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	ULagCompensationComponent();

	friend class APBCharacter;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ShowFramePackage(const FFramePackage& Package, const FColor& Color);

	UFUNCTION(Server, Reliable)
	void ServerScoreRequest(APBCharacter* HitCharacter, const FVector_NetQuantize& TraceStart, const FVector_NetQuantize& HitLocation, float HitTime, class AWeapon* DamageCauser);

protected:

	virtual void BeginPlay() override;

	FServerSideRewindResult ServerSideRewind(class APBCharacter* HitCharacter, const FVector_NetQuantize& TraceStart, const FVector_NetQuantize& HitLocation, float HitTime);

	void SaveFramePackage(FFramePackage& Package);

	FFramePackage InterpBetweenFrames(const FFramePackage& OlderFrame, const FFramePackage& YoungerFrame, float HitTime);

	FServerSideRewindResult ConfirmHit(const FFramePackage& Package, APBCharacter* HitCharacter, const FVector_NetQuantize& TraceStart, const FVector_NetQuantize& HitLocation);

	void CacheBoxPositions(APBCharacter* HitCharacter, FFramePackage& OutFramePackage);

	void MoveBoxes(APBCharacter* HitCharacter, const FFramePackage& Package);

	void ResetHitBoxes(APBCharacter* HitCharacter, const FFramePackage& Package);

	void EnableCharacterMeshCollision(APBCharacter* HitCharacter, ECollisionEnabled::Type CollisionEnabled);

	void SaveFramePackage();

	FFramePackage GetFrameToCheck(APBCharacter* HitCharacter, float HitTime);

	/**
	* Shotgun
	*/

	FShotgunServerSideRewindResult ShotgunServerSideRewind(const TArray<APBCharacter*>& HitCharacters, const FVector_NetQuantize& TraceStart, const TArray<FVector_NetQuantize>& HitLocation, float HitTime);

	FShotgunServerSideRewindResult ShotgunConfirmHit(const TArray<FFramePackage>& Package, const FVector_NetQuantize& TraceStart, const TArray<FVector_NetQuantize>& HitLocation);

private:

	UPROPERTY()
	APBCharacter* Character;

	UPROPERTY()
	class APBPlayerController* Controller;

	TDoubleLinkedList<FFramePackage> FrameHistory;

	UPROPERTY(EditAnywhere)
	float MaxRecordTime = 4.f;
		
};
