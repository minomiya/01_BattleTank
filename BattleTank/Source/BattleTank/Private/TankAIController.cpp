// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/TankAIController.h"
#include "Tank.h"

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (PlayerTank)
	{
		auto ControlledPlayer = Cast<ATank>(GetPawn());
		// Move towards the player

		// Aim towards the player
		ControlledPlayer->AimAt(PlayerTank->GetActorLocation());

		ControlledPlayer->Fire();
	}
}

