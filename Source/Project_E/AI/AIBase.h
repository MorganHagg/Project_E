#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIBase.generated.h"

UCLASS()
class PROJECT_E_API AAIBase : public AAIController
{
	GENERATED_BODY()

public:
	AAIBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void SetTargetLocation(FVector Location);

	// Blackboard names
	const FName BB_TargetLocation = TEXT("TargetLocation");
};
