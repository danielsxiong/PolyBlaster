// Fill out your copyright notice in the Description page of Project Settings.


#include "CaptureTheFlag/FlagZone.h"
#include "Components/SphereComponent.h"

#include "PBTypes/Team.h"
#include "Weapon/Flag.h"
#include "GameMode/PBCaptureTheFlagGameMode.h"

// Sets default values
AFlagZone::AFlagZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ZoneSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ZoneSphere"));
	SetRootComponent(ZoneSphere);
}

// Called when the game starts or when spawned
void AFlagZone::BeginPlay()
{
	Super::BeginPlay();
	
	ZoneSphere->OnComponentBeginOverlap.AddDynamic(this, &AFlagZone::OnSphereOverlap);
}

void AFlagZone::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweep)
{
	AFlag* OverlappingFlag = Cast<AFlag>(OtherActor);
	if (OverlappingFlag && OverlappingFlag->GetTeam() != Team)
	{
		APBCaptureTheFlagGameMode* GameMode = GetWorld()->GetAuthGameMode<APBCaptureTheFlagGameMode>();
		if (GameMode)
		{
			GameMode->FlagCaptured(OverlappingFlag, this);
			OverlappingFlag->ResetFlag();
		}
	}
}

