// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank/Public/TankBarrel.h"
//#include "Runtime/Engine/Classes/Engine/World.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	//UE_LOG(LogTemp, Warning, TEXT("Barrel elevate called"));

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto ClampElevation = FMath::Clamp(RawNewElevation, MinElevationInDegrees, MaxElevationInDegrees);

	SetRelativeRotation(FRotator(ClampElevation, 0, 0));
}
