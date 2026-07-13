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
	Super::BeginPlay();
	UnitManagerRef = GetGameInstance()->GetSubsystem<UUnitManager>();
	SpawnUnit();
}

void AUnitSpawner::SpawnUnit()
{
	if (!UnitManagerRef) return;
	UnitManagerRef->SpawnUnit(GetNextUnitRowName(), GetActorTransform());
}

FName AUnitSpawner::GetNextUnitRowName()
{
	if (UnitRowNames.Num() == 0) return NAME_None;
	if (UnitRowNames.Num() == 1) return UnitRowNames[0];

	if (SpawnMode == ESpawnSelectionMode::Sequential)
	{
		FName Result = UnitRowNames[SequentialIndex];
		SequentialIndex = (SequentialIndex + 1) % UnitRowNames.Num();
		return Result;
	}

	// WeightedRandom
	float TotalWeight = 0.f;
	for (int32 i = 0; i < UnitRowNames.Num(); i++)
	{
		TotalWeight += Weights.IsValidIndex(i) ? Weights[i].Value : 1.f;
	}

	float Roll = FMath::FRandRange(0.f, TotalWeight);
	float Cumulative = 0.f;
	for (int32 i = 0; i < UnitRowNames.Num(); i++)
	{
		Cumulative += Weights.IsValidIndex(i) ? Weights[i].Value : 1.f;
		if (Roll <= Cumulative)
		{
			return UnitRowNames[i];
		}
	}

	return UnitRowNames.Last(); // fallback, shouldn't hit
}

void AUnitSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// In editor function
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

