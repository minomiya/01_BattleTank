// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI controller not possesing a Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI controller %s possesing: %s"), *Super::GetName(), *ControlledTank->GetName());
	}
	
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}