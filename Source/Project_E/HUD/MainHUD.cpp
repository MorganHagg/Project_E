#include "MainHUD.h"
#include "../Unit/UnitBase.h"
#include "../Input/PlayerControls.h"

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();
	SetController();
}

void AMainHUD::SetController()
{
	Controller = Cast<APlayerControls>(GetWorld()->GetFirstPlayerController());
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
	   false, 
	   false	);
	}
}

void AMainHUD::StartSelection()
{
	Controller->GetMousePosition(PointA.X, PointA.Y);
	bIsDrawing = true;
}


// void AMainHUD::EndSelection()
TArray<class AUnitBase*> AMainHUD::EndSelection()
{
	bIsDrawing = false;
	return SelectedUnits;
}



	