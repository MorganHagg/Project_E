// Engine classes
#include "AIBase.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Actors/UnitBase.h"

AAIBase::AAIBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAIBase::BeginPlay()
{
	Super::BeginPlay();
	if (AUnitBase* Unit = Cast<AUnitBase>(GetPawn()))
	{
		if (Unit->BehaviorTree)
			RunBehaviorTree(Unit->BehaviorTree);
		else
			UE_LOG(LogTemp, Warning, TEXT("%s has no BehaviorTree assigned"), *Unit->GetName());
	}
}

void AAIBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAIBase::SetTargetLocation(FVector Location)
{
	UE_LOG(LogTemp, Log, TEXT("My Vector: %s"), *Location.ToString());
	GetBlackboardComponent()->SetValueAsVector(BB_TargetLocation, Location);
}

