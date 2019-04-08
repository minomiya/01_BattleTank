// Copyrights LateGameStudios Ltd.


#include "TankPlayerController.h"
#include "BattleTank.h"
#include "TankAimmingComponent.h"



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	TankAimmingComponent = GetPawn()->FindComponentByClass< UTankAimingComponent>();
	if (ensure(!TankAimmingComponent)){return; }
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!TankAimmingComponent){ return; }

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		TankAimmingComponent->AimAt(HitLocation);
	}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation)
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(CrossHairXLocation * ViewportSizeX, CrossHairYLocation * ViewportSizeY);

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		if (GetLookVectorHitLocation(LookDirection, HitLocation))
		{
			//UE_LOG(LogTemp, Warning, TEXT("OutHit: %s"), *HitLocation.ToString());
		}
	}

	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation)
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	FCollisionQueryParams TraceParameters = FCollisionQueryParams(FName(TEXT("")), false, TankAimmingComponent->Barrel);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility, TraceParameters))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	else
	{
		HitLocation = FVector(0);
		return false;
	}
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	// "De-project" the screen position of the crosshair to a word direction
	FVector CameraWorlLocation;
	if (DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorlLocation, 
		LookDirection))
	{
		return true;
	}

	return false;
}


