// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankNavMovementComponent.generated.h"

class UTankTrack;

/**
 * Responsable to move the tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankNavMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = TankInputs)
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = TankInputs)
	void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;

};
