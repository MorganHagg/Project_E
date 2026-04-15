#pragma once
// Engine classes
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
// Generated
#include "ControllerBase.generated.h"

class AUnitBase;

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

	void Initiate();
	FInputModeGameAndUI GameInput;

	// Input Actions
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* IMC_Camera;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* IMC_ControllUnits;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class AUnitBase*> SelectedUnits;

	void AddUnit(class AUnitBase* Unit);
	void ClearSelectedUnits();
};
