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
	}
}

void AMainHUD::StartSelection()
{
	GetOwningPlayerController()->GetMousePosition(PointA.X, PointA.Y);
	bIsDrawing = true;
	
}

void AMainHUD::EndSelection()
{
	bIsDrawing = false;
	TArray<AUnitBase*> SelectedUnits;
	bool NonCollidingComponent = false;
	bool MustBeFullySelected = false;
	GetActorsInSelectionRectangle<AUnitBase>(PointA, PointB, SelectedUnits, NonCollidingComponent, MustBeFullySelected);
	
}

void AMainHUD::SetController()
{
	Controller = Cast<AControllerBase>(GetWorld()->GetFirstPlayerController());
}
	