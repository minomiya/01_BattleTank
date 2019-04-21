// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/TankAIController.h"
#include "TankAimmingComponent.h"
#include "../Public/Tank.h"
#include "Runtime/Core/Public/Delegates/DelegateSignatureImpl.inl"


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

	if (!ensure(ControlledTank)) { return; }

	auto ControlledPlayer = GetPawn();

	if (!PlayerTank) { return; }
	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	// Aim towards the player
	auto TankAimmingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(TankAimmingComponent)) { return; }
	TankAimmingComponent->AimAt(PlayerTank->GetActorLocation());

	if (TankAimmingComponent->GetFiringStatus() == EFiringStatus::Locked)
	{
		TankAimmingComponent->Fire();
	}
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return;	}

		PossessedTank->TankIsDead.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

void ATankAIController::OnTankDeath()
{
	if (!PossessedTank) { return; }
	 
	PossessedTank->DetachFromControllerPendingDestroy();
	UE_LOG(LogTemp, Warning, TEXT("Game over %s is dead"), *GetName())
}
