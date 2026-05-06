// Engine classes
#include "PlayerControls.h"
#include "EnhancedInputComponent.h"
// Custom classes
#include "../HUD/MainHUD.h"
#include "../AI/AIUnit.h"
#include "../Unit/UnitBase.h"
#include "../Component/UnitHandler.h"

APlayerControls::APlayerControls()
{
	PrimaryActorTick.bCanEverTick = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	UnitHandler = CreateDefaultSubobject<UUnitHandler>(TEXT("UnitHandler"));
}


void APlayerControls::BeginPlay()
{
	Super::BeginPlay();
	SetUpReferences();
	InputSetup();
}

void APlayerControls::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerControls::SetUpReferences()
{
	HUD = Cast<AMainHUD>(GetHUD());
}

void APlayerControls::InputSetup()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = 
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IMC_Camera, 0);
		Subsystem->AddMappingContext(IMC_ControllUnits, 0);
	}

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		Input->BindAction(IA_Select, ETriggerEvent::Started, this, &APlayerControls::SelectStarted);
		Input->BindAction(IA_Select, ETriggerEvent::Completed, this, &APlayerControls::SelectReleased);
		Input->BindAction(IA_Command, ETriggerEvent::Started, this, &APlayerControls::CommandPressed);
		Input->BindAction(IA_Command, ETriggerEvent::Completed, this, &APlayerControls::CommandReleased);
		Input->BindAction(IA_ShiftSelect, ETriggerEvent::Started, this, &APlayerControls::ShiftPressed);
		Input->BindAction(IA_ShiftSelect, ETriggerEvent::Completed, this, &APlayerControls::ShiftReleased);
	}
	
	GameInput.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	GameInput.SetHideCursorDuringCapture(false);
	SetInputMode(GameInput);
}

void APlayerControls::SelectStarted()
{
	HUD->StartSelection();
	if (!bShiftHeld)
		ClearSelectedUnits();
}

void APlayerControls::SelectReleased()
{
	TArray<AUnitBase*> SelectedUnits;
	SelectedUnits = HUD->EndSelection();
		
	for (AUnitBase* Unit : SelectedUnits)
	{
		if (bool* bSelected = UnitHandler->Squad.Find(Unit))
			*bSelected = true;
	}
	UpdateSelectedUnits();
}

void APlayerControls::CommandPressed()
{
	FHitResult Hit;
	
	GetHitResultUnderCursor(ECC_Camera, false, Hit);

	if (AUnitBase* Target = Cast<AUnitBase>(Hit.GetActor()))
	{
		if (UnitHandler->IsInSquad(Target))
		{
			UE_LOG(LogTemp, Warning, TEXT("Friendly target"))
		}
		else
		{
			for (auto& Pair : UnitHandler->Squad)
			{
				if (Pair.Value == true)
				{
					Pair.Key->SetTarget(Target);
					Pair.Key->AIController->SetAction(EAction::Attacking);
				}
			}
		}
	}
	else
	{
		for (auto& Pair : UnitHandler->Squad)
		{
			if (Pair.Value == true)
			{
				Pair.Key->MoveTo(Hit.Location);
				Pair.Key->AIController->SetAction(EAction::Walking);
			}
		}
	}
}

void APlayerControls::CommandReleased()
{

}

void APlayerControls::ClearSelectedUnits()
{
	for (auto& Pair : UnitHandler->Squad)
	{
		Pair.Value = false;
	}
}

void APlayerControls::UpdateSelectedUnits()
{
	for (auto& Pair : UnitHandler->Squad)
	{
		if (Pair.Value == true)
			Pair.Key->DrawDecal();
		else
			Pair.Key->RemoveDecal();
	}
}
