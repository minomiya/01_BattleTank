// Copyrights LateGameStudios Ltd.


#include "BattleTank/Public/Tank.h"
#include "BattleTank/Public/Projectile.h"
#include "Runtime/Engine/Classes/Engine/StaticMeshSocket.h"
#include "BattleTank.h"
#include "BattleTank/Public/TankBarrel.h"
#include "TankAimmingComponent.h"


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	TankAimmingComponent = FindComponentByClass<UTankAimmingComponent>();

}

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::AimAt(FVector HitLocation)
{
	if (ensure(!TankAimmingComponent)) { return; }
	TankAimmingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (bIsReloaded && TankAimmingComponent && ProjectileBP)
	{

		FVector Location = TankAimmingComponent->Barrel->GetSocketLocation(FName("Projectile"));
		FRotator Rotation = TankAimmingComponent->Barrel->GetSocketRotation(FName("Projectile"));

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBP, Location, Rotation);

		Projectile->LaunchProjectile(LaunchSpeed);	
		LastFireTime = FPlatformTime::Seconds();
	}
}

