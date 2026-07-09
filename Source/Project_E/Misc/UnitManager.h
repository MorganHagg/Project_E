#pragma once
// Engine classes
#include "CoreMinimal.h"
// Custom classes
#include "../Public/UnitRowHandle.h"
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
	AUnitBase* SpawnUnit(FUnitRowHandle RowHandle, FVector Location);

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
