// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank/Public/TankBarrel.h"
//#include "Runtime/Engine/Classes/Engine/World.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	//UE_LOG(LogTemp, Warning, TEXT("Barrel elevate called"));
	
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	SetRelativeRotation(FRotator(RawNewElevation, 0, 0));
}
