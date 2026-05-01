#include "AICommander.h"

AAICommander::AAICommander()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAICommander::BeginPlay()
{
	Super::BeginPlay();
}

void AAICommander::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAICommander::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
