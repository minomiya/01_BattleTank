// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankTrack.h"
#include "BattleTank.h"


// Called when the game starts
void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
}

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	auto Wheels = GetWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();
	 
	for (ASprungWheel* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}

}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> ResultArray;

	TArray<USceneComponent*> Children;
	GetChildrenComponents(false, Children);

	for(USceneComponent* Child : Children)
	{
		USpawnPoint* SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild) continue;

		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();

		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SprungWheel) continue;

		ResultArray.Add(SprungWheel);
	}

	return ResultArray;
}
