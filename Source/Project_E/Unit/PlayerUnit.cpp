// Engine classes
#include "PlayerUnit.h"
#include "Kismet/GameplayStatics.h"

APlayerUnit::APlayerUnit()
{
	PrimaryActorTick.bCanEverTick = true;

	DecalMaterial = LoadObject<UMaterialInterface>(
	nullptr,
	TEXT("/Game/Assets/Decal/UnitTarget_Mat")
);
}

void APlayerUnit::BeginPlay()
{
	Super::BeginPlay();
	CreateDecal();
}

void APlayerUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerUnit::CreateDecal()
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
void APlayerUnit::DrawDecal()
{
	if (DecalComponent)
		DecalComponent->SetVisibility(true);
}

void APlayerUnit::RemoveDecal()
{
	if (DecalComponent)
		DecalComponent->SetVisibility(false);
}

void APlayerUnit::SetDecalColor(FLinearColor Color)
{
	if (!DecalMatInstance) return;
	DecalMatInstance->SetVectorParameterValue(TEXT("TintColor"), Color);
}