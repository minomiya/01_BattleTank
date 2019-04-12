// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

public:
	// Called when the game starts
	virtual void BeginPlay() override;

	void ApplySidewayForce();

	UTankTrack();

	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);

	void DriveTrack();

	// Max force per track in newtons
	UPROPERTY(EditDefaultsOnly, Category = Input)
	float TrackMaxDrivingForce = 40000000; // Assume 40 tonne tank, and 1g accelleration

	float CurrentThrottle = 0;
};
