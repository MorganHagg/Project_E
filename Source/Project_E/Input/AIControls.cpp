//Engine classes
#include "AIControls.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Project_E/Actors/AICommander.h"


AAIControls::AAIControls()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAIControls::BeginPlay()
{
	Super::BeginPlay();
}

void AAIControls::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	BehaviorTree = LoadObject<UBehaviorTree>(nullptr,
	TEXT("/Game/Framework/AI/AICommander/BT_AICommander.BT_AICommander"));
	if (BehaviorTree)
			RunBehaviorTree(BehaviorTree);
}

void AAIControls::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}