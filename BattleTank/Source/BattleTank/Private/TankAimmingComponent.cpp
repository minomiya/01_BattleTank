// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank/Public/TankAimmingComponent.h"
#include "BattleTank/Public/TankBarrel.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Called when the game starts
void UTankAimmingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimmingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Sets default values for this component's properties
UTankAimmingComponent::UTankAimmingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; // TODO shound this really tick?

	// ...
}

void UTankAimmingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimmingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FCollisionQueryParams TraceParameters = FCollisionQueryParams(FName(TEXT("")), false, Barrel);

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
		(
			this,
			OutLaunchVelocity,
			StartLocation,
			HitLocation,
			LaunchSpeed
		);
	

	auto Time = GetWorld()->GetTimeSeconds();

	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		UE_LOG(LogTemp, Warning, TEXT("%f Aim Solution found"), Time);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%f Aim Solution not found"), Time);
	}
}

void UTankAimmingComponent::MoveBarrelTowards(FVector AimDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(5); // TODO remove magic number
}


