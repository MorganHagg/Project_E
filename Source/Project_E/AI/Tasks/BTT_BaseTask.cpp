// Engine classes
#include "BTT_BaseTask.h"
#include "AIController.h"
#include "Project_E/Actors/UnitBase.h"

EBTNodeResult::Type UBTT_BaseTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	CachedOwnerComp = &OwnerComp;
	if (AUnitBase* Unit = GetMyUnit())
		OnExecute(Unit);
	return EBTNodeResult::InProgress;
}

void UBTT_BaseTask::FinishTask(bool bSuccess)
{
	if (CachedOwnerComp)
		FinishLatentTask(*CachedOwnerComp, bSuccess ? EBTNodeResult::Succeeded : EBTNodeResult::Failed);
}

AUnitBase* UBTT_BaseTask::GetMyUnit()
{
	if (!CachedOwnerComp) return nullptr;
	if (AAIController* AIC = Cast<AAIController>(CachedOwnerComp->GetAIOwner()))
		return Cast<AUnitBase>(AIC->GetPawn());
	return nullptr;
}