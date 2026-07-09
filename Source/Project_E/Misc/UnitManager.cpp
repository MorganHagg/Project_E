// Engine classes
#include "UnitManager.h"
#include "BehaviorTree/BehaviorTree.h"
// Custom classes
#include "../AI/AIUnit.h"
#include "../Public/UnitRowHandle.h"
#include "../Misc/FUnitSpawnDataRow.h"
#include "../Misc/FPlayerUnitParams.h"
#include "../Unit/UnitBase.h"
#include "../Unit/PlayerUnit.h"
#include "PaperZDAnimationComponent.h"

void UUnitManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UnitDataTable = LoadObject<UDataTable>(nullptr,
		TEXT("/Game/Framework/DataTable/DT_UnitSpawnData.DT_UnitSpawnData"));

	PlayerBehaviorTree = LoadObject<UBehaviorTree>(nullptr,
		TEXT("/Game/Framework/AI/BT_PlayerUnits.BT_PlayerUnits"));
}

AUnitBase* UUnitManager::SpawnUnit(FUnitRowHandle RowHandle, FVector Location)
{
	if (!UnitDataTable) return nullptr;

	FFUnitSpawnDataRow* Row = UnitDataTable->FindRow<FFUnitSpawnDataRow>(RowHandle.RowName, TEXT("SpawnUnit"));
	if (!Row) return nullptr;

	FTransform SpawnTransform(FRotator(0.f, 0.f, 90.f), Location);

	AUnitBase* NewUnit = Cast<AUnitBase>(
		GetWorld()->SpawnActorDeferred<AUnitBase>(
			AUnitBase::StaticClass(),
			SpawnTransform,
			nullptr,
			nullptr,
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn));

	if (!NewUnit) return nullptr;

	if (Row->AnimBP)
	{
		NewUnit->GetAnimationComponent()->SetAnimInstanceClass(Row->AnimBP);
	}

	NewUnit->FinishSpawning(SpawnTransform);

	NewUnit->BehaviorTree = Row->BehaviorTree;
	if (NewUnit->AIController && NewUnit->BehaviorTree)
		NewUnit->AIController->RunBehaviorTree(NewUnit->BehaviorTree);
	NewUnit->GrantedAbilities = Row->DefaultAbilities;
	NewUnit->Stats = Row->Stats;

	return NewUnit;
}

APlayerUnit* UUnitManager::SpawnPlayerUnit(FPlayerUnitParams SpawnParams, FVector Location)
{
	FTransform SpawnTransform(FRotator(0.f, 0.f, 90.f), Location);

	APlayerUnit* NewUnit = Cast<APlayerUnit>(
		GetWorld()->SpawnActorDeferred<APlayerUnit>(
			APlayerUnit::StaticClass(),
			SpawnTransform,
			nullptr,
			nullptr,
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn));

	if (!NewUnit) return nullptr;

	if (SpawnParams.AnimBP)
	{
		NewUnit->GetAnimationComponent()->SetAnimInstanceClass(SpawnParams.AnimBP);
	}

	NewUnit->FinishSpawning(SpawnTransform);
	NewUnit->BehaviorTree = PlayerBehaviorTree;
	if (NewUnit->AIController && NewUnit->BehaviorTree)
		NewUnit->AIController->RunBehaviorTree(NewUnit->BehaviorTree);

	return NewUnit;
}

void UUnitManager::WritePersistenSquad()
{
}

void UUnitManager::ReadPersistentSquad()
{
}
