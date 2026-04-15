#include "MainHUD.h"
#include "../Character/UnitBase.h"
#include "../Input/ControllerBase.h"

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();
	SetController();
}

void AMainHUD::DrawHUD()
{
	if (bIsDrawing)
	{		//TODO: Make this easier to read
		GetOwningPlayerController()->GetMousePosition(PointB.X, PointB.Y);
		DrawRect(DrawColor, PointA.X, PointA.Y, PointB.X - PointA.X, PointB.Y - PointA.Y);

		SelectedUnits.Empty();
		bool bSuccess = GetActorsInSelectionRectangle<AUnitBase>(
	   PointA, 
	   PointB, 
	   SelectedUnits, 
	   true, 
	   false	);
	}
}

void AMainHUD::StartSelection()
{
	GetOwningPlayerController()->GetMousePosition(PointA.X, PointA.Y);
	bIsDrawing = true;
}

void AMainHUD::EndSelection()
{
	for (AUnitBase* Units : SelectedUnits)
	{
		Controller->AddUnit(Units);
	}
	bIsDrawing = false;
}

void AMainHUD::TEST()
{
	UE_LOG(LogTemp, Warning, TEXT("SelectedUnits count: %d"), SelectedUnits.Num());
}		

void AMainHUD::SetController()
{
	Controller = Cast<AControllerBase>(GetWorld()->GetFirstPlayerController());
}
	