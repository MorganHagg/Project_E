#pragma once
// Engine classes
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
// Generated
#include "UnitHandler.generated.h"

class AUnitBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_E_API UUnitHandler : public UActorComponent
{
	GENERATED_BODY()

public:
	UUnitHandler();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void AddToSquad(AUnitBase* Unit);
	void RemoveFromSquad(AUnitBase* Unit);

	bool IsInSquad(AUnitBase* Unit);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<AUnitBase*, bool> Squad;
};
