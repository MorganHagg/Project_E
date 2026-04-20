#include "Commander.h"

ACommander::ACommander()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACommander::BeginPlay()
{
	Super::BeginPlay(); 
	
}

void ACommander::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}