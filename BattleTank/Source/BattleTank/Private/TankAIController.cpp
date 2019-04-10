// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/TankAIController.h"
#include "TankAimmingComponent.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
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
	auto TankAimmingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(TankAimmingComponent)) { return; }
	TankAimmingComponent->AimAt(PlayerTank->GetActorLocation());

	TankAimmingComponent->Fire();
}

