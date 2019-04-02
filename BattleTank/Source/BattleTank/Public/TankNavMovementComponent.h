// Copyrights LateGameStudios Ltd.

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
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);
	
	UFUNCTION(BlueprintCallable, Category = "Inputs")
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Inputs")
	void IntendTurnRight(float Throw);

private:
	// Called from the pathfinding logic by the AI controllers
	void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	
	UTankTrack* LeftTrack = nullptr;
	
	UTankTrack* RightTrack = nullptr;

};
