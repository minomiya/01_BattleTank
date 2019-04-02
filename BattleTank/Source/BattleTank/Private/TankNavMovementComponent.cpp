// Copyrights LateGameStudios Ltd.

#include "TankNavMovementComponent.h"
#include "TankTrack.h"

void UTankNavMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !LeftTrackToSet){ return; }

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankNavMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !LeftTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankNavMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !LeftTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankNavMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	float Throw = FVector::DotProduct(TankForward, AIForwardIntention);
	FVector TurnThrow = FVector::CrossProduct(TankForward, AIForwardIntention);

	IntendMoveForward(Throw);
	IntendTurnRight(TurnThrow.Z);
}
