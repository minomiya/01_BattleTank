// Copyrights LateGameStudios Ltd.

#include "BattleTank/Public/TankAimmingComponent.h"
#include "BattleTank/Public/TankBarrel.h"
#include "BattleTank/Public/TankTurret.h"
#include "../Public/Projectile.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = FPlatformTime::Seconds();
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else if(isBarrelMoving())
	{
		FiringStatus = EFiringStatus::Aiming;
	}
	else
	{
		FiringStatus = EFiringStatus::Locked;
	}
}

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; 

	// ...
}

void UTankAimingComponent::Initialise(UTankTurret * TurretToSet, UTankBarrel * BarrelToSet)
{
	if ( !ensure(BarrelToSet && TurretToSet) ) { return; }

	Turret = TurretToSet;
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
		(
			this,
			OutLaunchVelocity,
			StartLocation,
			HitLocation,
			LaunchSpeed,
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace
		);
	
	auto Time = GetWorld()->GetTimeSeconds();

	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveTurretBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveTurretBarrelTowards(FVector AimDirection)
{
	if (!ensure(Turret && Barrel)) { return; }

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	if (FMath::Abs(DeltaRotator.Yaw) < 180) {
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
	Barrel->Elevate(DeltaRotator.Pitch);
}


void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBP)) { return; }

	if (FiringStatus != EFiringStatus::Reloading)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBP, 
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);	
		LastFireTime = FPlatformTime::Seconds();
	}
}

bool UTankAimingComponent::isBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01);
}
