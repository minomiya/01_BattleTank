// Copyrights LateGameStudios Ltd.


#include "BattleTank/Public/Tank.h"
#include "BattleTank.h"


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	
	
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<int32>(DamageAmount, 0, CurrentHealth);
	CurrentHealth -= DamageToApply;

	UE_LOG(LogTemp, Warning, TEXT("%s currentHealth %d DamageToApply %d DamagePoints %d"), *GetName(), CurrentHealth, DamageToApply, DamagePoints)

	return DamageToApply;
}


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}
