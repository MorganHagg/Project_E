// Engine classes
#include "GameFramework/Controller.h"
#include "UnitManager.h"
// Custom classes
#include "../Component/UnitHandler.h"
#include "../Unit/UnitBase.h"

AUnitBase* UUnitManager::SpawnUnit(EUnitArchetype Archetype, FVector Location, AController* Controller)
{
	FRotator Rotation = FRotator(FRotator::ZeroRotator);
	if (UUnitHandler* Handler = Controller->GetComponentByClass<UUnitHandler>())
	{
		AUnitBase* NewUnit = GetWorld()->SpawnActor<AUnitBase>(
		AUnitBase::StaticClass(),
		Location,
		Rotation);

		NewUnit->SetArchetype(Archetype);
		Handler->AddToSquad(NewUnit);
		return NewUnit;
	}
	return nullptr;
}

void UUnitManager::WritePersistenSquad()
{
}

void UUnitManager::ReadPersistenSquad()
{
}
