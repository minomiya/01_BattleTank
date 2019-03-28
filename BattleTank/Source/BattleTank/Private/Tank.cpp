// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank/Public/Tank.h"
#include "BattleTank.h"
#include "TankAimmingComponent.h"



// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimmingComponent = CreateDefaultSubobject<UTankAimmingComponent>(FName("Aimming Component"));
}

void ATank::AimAt(FVector HitLocation)
{
	TankAimmingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	TankAimmingComponent->SetBarrelReference(BarrelToSet);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

