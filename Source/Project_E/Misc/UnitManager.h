#pragma once
// Engine classes
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Subsystems/GameInstanceSubsystem.h"
// Custom classes
// Generated
#include "UnitManager.generated.h"

class AController;
class UAbility;
class UBehaviorTree;
struct FPlayerUnitParams;

USTRUCT()
struct FUnitSaveData
{
	GENERATED_BODY()

	TArray<TSubclassOf<UAbility>> Abilities;
	// gear etc
};

UCLASS()
class PROJECT_E_API UUnitManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	UFUNCTION(BlueprintCallable)
	AUnitBase* SpawnUnit(FName RowName, const FTransform& SpawnTransform);

	UFUNCTION(BlueprintCallable)
	APlayerUnit* SpawnPlayerUnit(FPlayerUnitParams SpawnParams, FVector Location);
	
	void WritePersistenSquad();

	void ReadPersistentSquad();
	
	TArray<FUnitSaveData> PersistenSquad;

	UPROPERTY(BlueprintReadOnly)
	UDataTable* UnitDataTable;

	UFUNCTION(BlueprintCallable)
	TArray<FName> GetSpawnableArchetypes() const
	{
		if (!UnitDataTable) return {};
		return UnitDataTable->GetRowNames();
	}

	UPROPERTY(EditAnywhere, Category = "AI")
	UBehaviorTree* PlayerBehaviorTree;
};
