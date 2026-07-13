#pragma once
// Engine classes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
// Custom classes
#include "../Public/UnitRowHandle.h"
// Generated
#include "UnitSpawner.generated.h"


class AUnitBase;
class UUnitManager;

UCLASS()
class PROJECT_E_API AUnitSpawner : public AActor
{
	GENERATED_BODY()

public:
	AUnitSpawner();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, Category = "Unit Spawner")
	UUnitManager* UnitManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Spawner")
	FUnitRowHandle UnitArchetype;

	UPROPERTY(EditAnywhere, Category = "Unit Spawner")
	UDataTable* UnitDataTable;
	
	UPROPERTY(EditAnywhere, meta = (GetOptions = "GetValidUnitRowNames"))
	FName UnitRowName;
	
	UFUNCTION(CallInEditor)
	TArray<FString> GetValidUnitRowNames() const;
};
	