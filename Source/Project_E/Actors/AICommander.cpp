// Engine classes
#include "AICommander.h"
// Custom classes
#include "../Misc/UnitManager.h"
#include "../Input/AIControls.h"

AAICommander::AAICommander()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AAIControls::StaticClass();
}

void AAICommander::BeginPlay()
{
	Super::BeginPlay();
	
	UUnitManager* UnitManager = GetGameInstance()->GetSubsystem<UUnitManager>();
	UnitManager->SpawnUnit(EUnitArchetype::Warrior, GetActorLocation(), EUnitFaction::Hostile);
}

void AAICommander::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAICommander::SetAIController(AAIController* NewAIController)
{
}
