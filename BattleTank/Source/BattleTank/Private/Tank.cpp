// Copyrights LateGameStudios Ltd.


#include "BattleTank/Public/Tank.h"
#include "BattleTank/Public/Projectile.h"
#include "Runtime/Engine/Classes/Engine/StaticMeshSocket.h"
#include "BattleTank.h"
#include "BattleTank/Public/TankBarrel.h"


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

}

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}


void ATank::Fire()
{
	//if (ensure(!Barrel)) { return; }
	//bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	//if (bIsReloaded) // TODO refactor the fire function
	//{
	//	auto Projectile = GetWorld()->SpawnActor<AProjectile>(
	//		ProjectileBP, 
	//		Barrel->GetSocketLocation(FName("Projectile")),
	//		Barrel->GetSocketRotation(FName("Projectile"))
	//		);

	//	Projectile->LaunchProjectile(LaunchSpeed);	
	//	LastFireTime = FPlatformTime::Seconds();
	//}
}

