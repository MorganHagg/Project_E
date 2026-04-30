#pragma once
// Engine classes
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
// Generated
#include "ControllerBase.generated.h"

class AUnitBase;
class AMainHUD;

UCLASS()
class PROJECT_E_API AControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	AControllerBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void SetUpReferences();
	void InputSetup();
	FInputModeGameAndUI GameInput;

	// Input Actions
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* IMC_Camera;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* IMC_ControllUnits;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_Select;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_Command;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_ShiftSelect;

	void SelectStarted();
	void SelectReleased();
	
	void CommandPressed();
	void CommandReleased();

	bool bShiftHeld = false;
	void ShiftPressed()   { bShiftHeld = true; };
	void ShiftReleased()   { bShiftHeld = false; };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<AUnitBase*, bool> Squad;

	
	void AddToSquad(class AUnitBase* Unit);
	void RemoveFromSquad(class AUnitBase* Unit);
	
	void ClearSelectedUnits();
	void UpdateSelectedUnits();

	AMainHUD* HUD;

};