// Engine classes
#include "UnitSpawner.h"
#include "Engine/GameInstance.h"
#include "UObject/ConstructorHelpers.h"
// Custom classes
#include "../Misc/UnitManager.h"
#include "../Unit/UnitBase.h"

AUnitSpawner::AUnitSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableFinder(
	TEXT("/Game/Framework/DataTable/DT_UnitSpawnData.DT_UnitSpawnData")
);

	if (DataTableFinder.Succeeded())
	{
		UnitDataTable = DataTableFinder.Object;
	}
}

void AUnitSpawner::BeginPlay()
{
	UnitManager = GetGameInstance()->GetSubsystem<UUnitManager>();
	Super::BeginPlay();
}

void AUnitSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TArray<FString> AUnitSpawner::GetValidUnitRowNames() const
{
	TArray<FString> RowNames;
	
	if (!UnitDataTable)
	{
		return RowNames;
	}

	for (const FName& RowName : UnitDataTable->GetRowNames())
	{
		RowNames.Add(RowName.ToString());
	}

	return RowNames;
}

