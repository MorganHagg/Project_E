// Engine classes
#include "TargetLocation.h"

ATargetLocation::ATargetLocation()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATargetLocation::BeginPlay()
{
	Super::BeginPlay();
	
}
void ATargetLocation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

