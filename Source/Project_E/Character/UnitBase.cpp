// Engine classes
#include "UnitBase.h"
#include "Components/CapsuleComponent.h"
// Custom classes
#include "../Input/ControllerBase.h"

AUnitBase::AUnitBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	DecalMaterial = LoadObject<UMaterialInterface>(
		nullptr,
		TEXT("/Game/Assets/Decal/UnitTarget_Mat")
	);
}

void AUnitBase::BeginPlay()
{
	Super::BeginPlay();
	CreateDecal();
	SetController();
}

void AUnitBase::CreateDecal()
{
	if (GetMesh())
		GetMesh()->bReceivesDecals = false;

	if (!DecalMaterial) return;

	DecalMatInstance = UMaterialInstanceDynamic::Create(DecalMaterial, this);

	FRotator DecalRotation = FRotator(-90.f, 0.f, 0.f);

	FVector DecalLocation = GetActorLocation();
	DecalLocation.Z -= 90.f;

	DecalComponent = UGameplayStatics::SpawnDecalAttached(
		DecalMatInstance,
		FVector (DecalThickness, DecalSize, DecalSize),
		GetRootComponent(),
		NAME_None,
		DecalLocation,
		DecalRotation,
		EAttachLocation::KeepWorldPosition,
		0.f
	);
	DecalComponent->SetVisibility(false);	// Starts the unit with decal off
	
}

void AUnitBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUnitBase::ToggleSelect()
{
	if (!Controller) return;

	if (bool* bSelected = Controller->Squad.Find(this))
	{
		*bSelected = !(*bSelected);
	}
	
}

void AUnitBase::DrawDecal()
{
	if (DecalComponent)
		DecalComponent->SetVisibility(true);
}

void AUnitBase::RemoveDecal()
{
	if (DecalComponent)
		DecalComponent->SetVisibility(false);
}

void AUnitBase::SetDecalColor(FLinearColor Color)
{
	if (!DecalMatInstance) return;
	DecalMatInstance->SetVectorParameterValue(TEXT("TintColor"), Color);
}

void AUnitBase::SetController()
{
	Controller = Cast<AControllerBase>(GetWorld()->GetFirstPlayerController());
	Controller->Squad.Add(this, false);
}

void AUnitBase::SetUnitType(EUnitType NewType)
{
	UnitType = NewType;
	switch (UnitType)
	{
	case EUnitType::Controlled:
		UE_LOG(LogTemp, Warning, TEXT("I am now controlled"))
		Controller->AddToSquad(this);
		break;
	case EUnitType::Friendly:
		UE_LOG(LogTemp, Warning, TEXT("I am now friendly!"))
		break;
	case EUnitType::Hostile:
		if (Controller->Squad.Contains(this))
			Controller->RemoveFromSquad(this);
		UE_LOG(LogTemp, Warning, TEXT("I am now hostile!"))	
		break;
	}
}

void AUnitBase::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Attacking unit"));
}

void AUnitBase::MoveTo()
{
	UE_LOG(LogTemp, Warning, TEXT("Moving unit"));
}
	