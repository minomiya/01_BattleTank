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

	auto PlayerTank = GetPlayerTank();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller not possesing a Player Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller %s possesing Player: %s"), *Super::GetName(), *PlayerTank->GetName());
	}
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank = GetPlayerTank();
	if (PlayerTank)
	{
		// Move towards the player

		// Aim towards the player
		GetControlledTank()->AimAt(PlayerTank->GetActorLocation());

		// Fire if ready
	}

	FVector HitLocation(0);
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
