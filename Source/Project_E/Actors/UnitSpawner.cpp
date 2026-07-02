// Engine classes
#include "UnitSpawner.h"
// Custom classes
#include "../Misc/UnitManager.h"
#include "../Unit/UnitBase.h"

AUnitSpawner::AUnitSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AUnitSpawner::BeginPlay()
{
	UnitManager = GetGameInstance()->GetSubsystem<UUnitManager>();
	Super::BeginPlay();
}

void AUnitSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

