// Engine classes
#include "AIUnit.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Unit/UnitBase.h"

AAIUnit::AAIUnit()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAIUnit::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (AUnitBase* Unit = Cast<AUnitBase>(InPawn))
	{
		Unit->SetAIController(this);
	}
}

void AAIUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAIUnit::SetDestination(FVector Location)
{
	GetBlackboardComponent()->SetValueAsVector(BB_Destination, Location);
}

void AAIUnit::SetTarget(AUnitBase* Target)
{
	GetBlackboardComponent()->SetValueAsObject(BB_Target, Target);
}

AUnitBase* AAIUnit::GetTarget()
{
	return Cast<AUnitBase>(GetBlackboardComponent()->GetValueAsObject(BB_Target));;
}

void AAIUnit::ClearTarget()
{
	GetBlackboardComponent()->SetValueAsObject(BB_Target, nullptr);
}

void AAIUnit::SetInRange(bool bInRange)
{
	GetBlackboardComponent()->SetValueAsBool(BB_bInRange, bInRange);
}

void AAIUnit::SetAction(EAction Action)
{
	GetBlackboardComponent()->SetValueAsEnum(BB_Action, static_cast<int>(Action));
}