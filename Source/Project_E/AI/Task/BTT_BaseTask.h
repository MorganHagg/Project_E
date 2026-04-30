#pragma once
// Engine classes
#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
// Generated
#include "BTT_BaseTask.generated.h"

class AUnitBase;

UCLASS(Blueprintable)
class PROJECT_E_API UBTT_BaseTask : public UBTTaskNode
{
    GENERATED_BODY()

public:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    UFUNCTION(BlueprintImplementableEvent)
    void OnExecute(AUnitBase* Unit);

    UFUNCTION(BlueprintCallable)
    void FinishTask(bool bSuccess);

    UFUNCTION(BlueprintCallable)
    AUnitBase* GetMyUnit();

private:
    UBehaviorTreeComponent* CachedOwnerComp = nullptr;
};