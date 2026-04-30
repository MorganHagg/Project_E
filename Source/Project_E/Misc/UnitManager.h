#pragma once
// Engine classes
#include "CoreMinimal.h"
#include "../Actors/UnitBase.h"
// Generated
#include "UnitManager.generated.h"

USTRUCT()
struct FUnitSaveData
{
	GENERATED_BODY()

	EUnitArchetype Archetype;
	TMap<EStat, int32> Stats;
	TArray<TSubclassOf<UAbility>> Abilities;
	// gear etc
};

UCLASS()
class PROJECT_E_API UUnitManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	AUnitBase* SpawnUnit(EUnitArchetype Archetype, FVector Location, EUnitFaction Faction);
	
	void WritePersistenSquad();

	void ReadPersistenSquad();
	
	TArray<FUnitSaveData> PersistenSquad;
};
