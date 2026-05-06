#pragma once
// Engine classes
#include "CoreMinimal.h"
// Generated
#include "UnitManager.generated.h"

class AController;
class UUnitHandler;
class UAbility;

USTRUCT()
struct FUnitSaveData
{
	GENERATED_BODY()

	EUnitArchetype Archetype;
	TArray<TSubclassOf<UAbility>> Abilities;
	// gear etc
};

UCLASS()
class PROJECT_E_API UUnitManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	AUnitBase* SpawnUnit(EUnitArchetype Archetype, FVector Location, AController* Controller);
	
	void WritePersistenSquad();

	void ReadPersistenSquad();
	
	TArray<FUnitSaveData> PersistenSquad;
};
