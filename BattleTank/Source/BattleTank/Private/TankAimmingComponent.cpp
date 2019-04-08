// Copyrights LateGameStudios Ltd.

#include "BattleTank/Public/TankAimmingComponent.h"
#include "BattleTank/Public/TankBarrel.h"
#include "BattleTank/Public/TankTurret.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false; 

	// ...
}

void UTankAimingComponent::Initialise(UTankTurret * TurretToSet, UTankBarrel * BarrelToSet)
{
	if ( ensure(!BarrelToSet || !TurretToSet) ) { return; }

	Turret = TurretToSet;
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (ensure(!Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FCollisionQueryParams TraceParameters = FCollisionQueryParams(FName(TEXT("")), false, Barrel);

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
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveTurretBarrelTowards(AimDirection);
		//UE_LOG(LogTemp, Warning, TEXT("%f Aim Solution found"), Time);
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("%f Aim Solution not found"), Time);
	}
}

void UTankAimingComponent::MoveTurretBarrelTowards(FVector AimDirection)
{
	if (ensure(!Turret || !Barrel)) { return; }

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Turret->Rotate(DeltaRotator.Yaw);
	Barrel->Elevate(DeltaRotator.Pitch);
}


