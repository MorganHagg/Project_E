#pragma once
// Engine classes
#include "CoreMinimal.h"
#include "AIController.h"
// Generated
#include "AIControls.generated.h"

class AUnitBase;
class UUnitHandler;

UCLASS()
class PROJECT_E_API AAIControls : public AAIController
{
	GENERATED_BODY()

public:
	AAIControls();

protected:
	virtual void BeginPlay() override;
	
	virtual void OnPossess(APawn* InPawn) override;
	UPROPERTY()
	UBehaviorTree* BehaviorTree;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly)
	UUnitHandler* UnitHandler;
};
