#pragma once
// Engine classes
#include "GameFramework/HUD.h"
#include "CoreMinimal.h"
// Generated
#include "MainHUD.generated.h"

class APlayerUnit;
class APlayerControls;

UCLASS()
class PROJECT_E_API AMainHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;
	void SetController();
	
	UFUNCTION(BlueprintCallable)
	void StartSelection();
	UFUNCTION(BlueprintCallable)
	TArray<class APlayerUnit*> EndSelection();
	TArray<APlayerUnit*> SelectedUnits;
	
	APlayerControls* Controller = nullptr;
	FVector2D PointA;
	FVector2D PointB;
	bool bIsDrawing = false;
	FLinearColor DrawColor = FLinearColor(0.f, 0.f, 0.f, 0.7f);
};
