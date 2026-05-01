#include "UnitManager.h"

AUnitBase* UUnitManager::SpawnUnit(EUnitArchetype Archetype, FVector Location, EUnitFaction Faction)
{
	FRotator Rotation = FRotator(FRotator::ZeroRotator);
	AUnitBase* NewUnit = GetWorld()->SpawnActor<AUnitBase>(
		AUnitBase::StaticClass(),
		Location,
		Rotation);

	NewUnit->SetArchetype(Archetype);
	NewUnit->SetFaction(Faction);
	return NewUnit;
}

void UUnitManager::WritePersistenSquad()
{
}

void UUnitManager::ReadPersistenSquad()
{
}
