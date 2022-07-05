// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuffComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POLYBLASTER_API UBuffComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UBuffComponent();

	friend class APBCharacter;

protected:

	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY()
	class APBCharacter* Character;
};
