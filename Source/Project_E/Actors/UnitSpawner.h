#pragma once
// Engine classes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
// Custom classes
// Generated
#include "UnitSpawner.generated.h"

UENUM(BlueprintType)
enum class ESpawnSelectionMode : uint8
{
	Sequential,
	WeightedRandom
};

USTRUCT(BlueprintType)
struct FSpawnWeight
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Value = 1.0f;
};


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
	
	void SpawnUnit();
	
	FName GetNextUnitRowName();
	
public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Spawner")
	ESpawnSelectionMode SpawnMode = ESpawnSelectionMode::Sequential;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Spawner",
		meta = (EditCondition = "SpawnMode == ESpawnSelectionMode::WeightedRandom"))
	TArray<FSpawnWeight> Weights;
	
	UPROPERTY(EditAnywhere, meta = (GetOptions = "GetValidUnitRowNames"))
	TArray<FName> UnitRowNames;
	
	UPROPERTY(BlueprintReadOnly, Category = "Unit Spawner")
	UUnitManager* UnitManagerRef;

	UPROPERTY(EditAnywhere, Category = "Unit Spawner")
	UDataTable* UnitDataTable;
	
	
	UFUNCTION(CallInEditor)
	TArray<FString> GetValidUnitRowNames() const;

private:
	int32 SequentialIndex = 0;
};
	