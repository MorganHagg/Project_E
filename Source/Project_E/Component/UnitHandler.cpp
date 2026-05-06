// Engine classes
#include "UnitHandler.h"
// Custom classes
#include "../Unit/UnitBase.h"

UUnitHandler::UUnitHandler()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UUnitHandler::BeginPlay()
{
	Super::BeginPlay();
	
}

void UUnitHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UUnitHandler::AddToSquad(AUnitBase* Unit)
{
	Squad.Add(Unit);
	Unit->SetHandler(this);
}

void UUnitHandler::RemoveFromSquad(AUnitBase* Unit)
{
	Squad.Remove(Unit);
}

bool UUnitHandler::IsInSquad(AUnitBase* Unit)
{
	return Squad.Contains(Unit);
}

