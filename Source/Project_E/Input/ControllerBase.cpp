// Engine classes
#include "ControllerBase.h"
#include "../Character/UnitBase.h"
#include "EnhancedInputComponent.h"
// Custom classes
#include "../HUD/MainHUD.h"

AControllerBase::AControllerBase()
{
	PrimaryActorTick.bCanEverTick = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}


void AControllerBase::BeginPlay()
{
	Super::BeginPlay();
	SetHUDRef();
	InputSetup();
}

void AControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AControllerBase::SetHUDRef()
{
	HUD = Cast<AMainHUD>(GetHUD());
}

void AControllerBase::InputSetup()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = 
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IMC_Camera, 0);
		Subsystem->AddMappingContext(IMC_ControllUnits, 0);
	}

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		Input->BindAction(IA_Select, ETriggerEvent::Started, this, &AControllerBase::SelectStarted);
		Input->BindAction(IA_Select, ETriggerEvent::Completed, this, &AControllerBase::SelectReleased);
		Input->BindAction(IA_Command, ETriggerEvent::Started, this, &AControllerBase::CommandPressed);
		Input->BindAction(IA_Command, ETriggerEvent::Completed, this, &AControllerBase::CommandReleased);
		Input->BindAction(IA_ShiftSelect, ETriggerEvent::Started, this, &AControllerBase::ShiftPressed);
		Input->BindAction(IA_ShiftSelect, ETriggerEvent::Completed, this, &AControllerBase::ShiftReleased);
	}
	
	GameInput.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	GameInput.SetHideCursorDuringCapture(false);
	SetInputMode(GameInput);
}

void AControllerBase::SelectStarted()
{
	HUD->StartSelection();
	if (!bShiftHeld)
		ClearSelectedUnits();
}

void AControllerBase::SelectReleased()
{
	TArray<AUnitBase*> SelectedUnits;
	SelectedUnits = HUD->EndSelection();
		
	for (AUnitBase* Unit : SelectedUnits)
	{
		if (Squad.Contains(Unit))
			Unit->ToggleSelect();
	}
	UpdateSelectedUnits();
}

void AControllerBase::CommandPressed()
{
	FHitResult Hit;
	
	GetHitResultUnderCursor(ECC_Camera, false, Hit);

	if (AUnitBase* Target = Cast<AUnitBase>(Hit.GetActor()))
	{
		switch (Target->UnitType)
		{
		case EUnitType::Controlled:
			UE_LOG(LogTemp, Warning, TEXT("Friendly target"))
			break;	// Do nothing
		case EUnitType::Friendly:
			break;
		case EUnitType::Hostile:
			for (auto& Pair : Squad)
			{
				if (Pair.Value == true)
					Pair.Key->Attack();
			}
			break;
		}
	}
	else
	{
		for (auto& Pair : Squad)
		{
			if (Pair.Value == true)
				Pair.Key->MoveTo();
		}
	}
}

void AControllerBase::CommandReleased()
{

}

void AControllerBase::AddToSquad(class AUnitBase* Unit)
{
	Squad.Add(Unit, false);
}

void AControllerBase::RemoveFromSquad(class AUnitBase* Unit)
{
	Squad.Remove(Unit);
}


void AControllerBase::ClearSelectedUnits()
{
	for (auto& Pair : Squad)
	{
		Pair.Value = false;
	}
}

void AControllerBase::UpdateSelectedUnits()
{
	for (auto& Pair : Squad)
	{
		if (Pair.Value == true)
			Pair.Key->DrawDecal();
		else
			Pair.Key->RemoveDecal();
	}
}
