#pragma once
// Engine classes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetLocation.generated.h"

UCLASS()
class PROJECT_E_API ATargetLocation : public AActor
{
	GENERATED_BODY()

public:
	ATargetLocation();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	float LifeTime;
	float TickInterval;
};
