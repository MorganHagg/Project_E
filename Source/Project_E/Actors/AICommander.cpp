// Engine classes
#include "AICommander.h"
// Custom classes
#include "../Input/AIControls.h"
#include "../Unit/UnitBase.h"

AAICommander::AAICommander()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AAIControls::StaticClass();
}

void AAICommander::BeginPlay()
{
	Super::BeginPlay();
}

void AAICommander::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

