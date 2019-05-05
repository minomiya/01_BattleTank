// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "../Public/SpawnPoint.h"
#include "../Public/SprungWheel.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
private:

public:
	// Called when the game starts
	virtual void BeginPlay() override;

	UTankTrack();

	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);

	void DriveTrack(float CurrentThrottle);

	// Max force per track in newtons
	UPROPERTY(EditDefaultsOnly, Category = Input)
	float TrackMaxDrivingForce = 40000000; // Assume 40 tonne tank, and 1g accelleration

	TArray<class ASprungWheel*> GetWheels() const;
};
