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

void AAIBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (AUnitBase* Unit = Cast<AUnitBase>(InPawn))
	{
		Unit->SetAIController(this);
		
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

void AAIBase::SetDestination(FVector Location)
{
	GetBlackboardComponent()->SetValueAsVector(BB_Destination, Location);
}

void AAIBase::SetTarget(AUnitBase* Target)
{
	GetBlackboardComponent()->SetValueAsObject(BB_Target, Target);
}

AUnitBase* AAIBase::GetTarget()
{
	return Cast<AUnitBase>(GetBlackboardComponent()->GetValueAsObject(BB_Target));;
}

void AAIBase::ClearTarget()
{
	GetBlackboardComponent()->SetValueAsObject(BB_Target, nullptr);
}
