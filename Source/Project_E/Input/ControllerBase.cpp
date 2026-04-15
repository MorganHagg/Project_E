#include "ControllerBase.h"

AControllerBase::AControllerBase()
{
	PrimaryActorTick.bCanEverTick = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void AControllerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

