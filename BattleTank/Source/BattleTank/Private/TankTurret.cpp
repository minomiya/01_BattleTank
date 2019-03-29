// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	// TODO figure out how to look back properly
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	auto RotatioChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotatio = RelativeRotation.Yaw + RotatioChange;
	
	//UE_LOG(LogTemp, Warning, TEXT("RawNewRotatio: %f"), RotatioChange);

	SetRelativeRotation(FRotator(0, Rotatio, 0));
}