#pragma once
// Engine classes
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
// Generated
#include "PlayerControls.generated.h"

class AUnitBase;
class APlayerUnit;
class AMainHUD;

UCLASS()
class PROJECT_E_API APlayerControls : public APlayerController
{
	GENERATED_BODY()

public:
	APlayerControls();

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
	
	void ClearSelectedUnits();
	void UpdateSelectedUnits();

	AMainHUD* HUD;

	// Squad
	void AddToSquad(APlayerUnit* Unit);
	void RemoveFromSquad(APlayerUnit* Unit);

	bool IsInSquad(APlayerUnit* Unit);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<APlayerUnit*, bool> Squad;

	void SquadMove(FVector Location);

	void SquadAttack(AUnitBase* Target);

};