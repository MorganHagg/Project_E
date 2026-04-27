#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIBase.generated.h"

class AUnitBase;

UCLASS()
class PROJECT_E_API AAIBase : public AAIController
{
	GENERATED_BODY()

public:
	AAIBase();
protected:
	virtual void OnPossess(APawn* InPawn) override;
public:
	virtual void Tick(float DeltaTime) override;

	void SetDestination(FVector Location);
	void SetTarget(AUnitBase* Target);
	AUnitBase* GetTarget();
	void ClearTarget();

	// Blackboard names
	const FName BB_Destination = TEXT("Destination");
	const FName BB_Target = TEXT("Target");
};
