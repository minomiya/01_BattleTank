// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/TankAIController.h"
#include "TankAimmingComponent.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	TankAimmingComponent = GetPawn()->FindComponentByClass< UTankAimingComponent>();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }

	auto ControlledPlayer = GetPawn();

	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	// Aim towards the player
	if (ensure(!TankAimmingComponent)) { return; }
	TankAimmingComponent->AimAt(PlayerTank->GetActorLocation());

	// TODO fix the fire()
	//ControlledPlayer->Fire(); 
}

