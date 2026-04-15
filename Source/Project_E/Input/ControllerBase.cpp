#include "ControllerBase.h"
#include "../Character/UnitBase.h"

AControllerBase::AControllerBase()
{
	PrimaryActorTick.bCanEverTick = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}


void AControllerBase::BeginPlay()
{
	Super::BeginPlay();
	Initiate();
}

void AControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AControllerBase::Initiate()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = 
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IMC_Camera, 0);
		Subsystem->AddMappingContext(IMC_ControllUnits, 0);
	}
	
	GameInput.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	GameInput.SetHideCursorDuringCapture(false);
	SetInputMode(GameInput);
}

void AControllerBase::AddUnit(class AUnitBase* Unit)
{
	UE_LOG(LogTemp, Log, TEXT("Adding unit %s"), *Unit->GetName());
	SelectedUnits.AddUnique(Unit);
	Unit->DrawDecal();
}

void AControllerBase::ClearSelectedUnits()
{
	for (class AUnitBase* UnitBase : SelectedUnits)
	{
		UnitBase->RemoveDecal();
	}
	SelectedUnits.Empty();
}


