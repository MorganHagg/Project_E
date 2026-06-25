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

	FActorSpawnParameters SpawnCollision;
	SpawnCollision.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	AUnitBase* NewUnit = GetWorld()->SpawnActor<AUnitBase>(
		AUnitBase::StaticClass(),
		Location,
		FRotator::ZeroRotator,
		SpawnCollision);

	if (!NewUnit) return nullptr;

	NewUnit->GetMesh()->SetSkeletalMesh(Row->Mesh);
	NewUnit->FixLocAndRot();
	NewUnit->BehaviorTree = Row->BehaviorTree;
	if (NewUnit->AIController && NewUnit->BehaviorTree)
		NewUnit->AIController->RunBehaviorTree(NewUnit->BehaviorTree);
	NewUnit->GrantedAbilities = Row->DefaultAbilities;
	NewUnit->Stats = Row->Stats;

	return NewUnit;
}

APlayerUnit* UUnitManager::SpawnPlayerUnit(FPlayerUnitParams SpawnParams, FVector Location)
{
	FActorSpawnParameters SpawnCollision;
	SpawnCollision.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	APlayerUnit* NewUnit = GetWorld()->SpawnActor<APlayerUnit>(
		APlayerUnit::StaticClass(),
		Location,
		FRotator::ZeroRotator,
		SpawnCollision);

	if (!NewUnit) return nullptr;

	NewUnit->GetMesh()->SetSkeletalMesh(SpawnParams.Mesh);
	NewUnit->FixLocAndRot();
	NewUnit->BehaviorTree = PlayerBehaviorTree;
	if (NewUnit->AIController && NewUnit->BehaviorTree)
		NewUnit->AIController->RunBehaviorTree(NewUnit->BehaviorTree);

	return NewUnit;
}

void UUnitManager::WritePersistenSquad()
{
}

void UUnitManager::ReadPersistenSquad()
{
}
