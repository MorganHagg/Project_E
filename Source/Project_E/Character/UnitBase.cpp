// Engine classes
#include "UnitBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

AUnitBase::AUnitBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	DecalMaterial = LoadObject<UMaterialInterface>(
		nullptr,
		TEXT("/Game/Assets/Decal/UnitTarget_Mat")
	);

	// SelectionVolume allows leniency as to where the player can click on a unit and still have it register
	SelectionVolume = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SelectionVolume"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderAsset(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	if (CylinderAsset.Succeeded())
	{
		SelectionVolume->SetStaticMesh(CylinderAsset.Object);
		SelectionVolume->SetupAttachment(RootComponent);
		SelectionVolume->bHiddenInGame = true;
		SelectionVolume->SetVisibility(false);
	}
}

void AUnitBase::BeginPlay()
{
	Super::BeginPlay();
	
	CreateDecal();
	if (GetMesh())
		GetMesh()->bReceivesDecals = false;
	SetUpCylinder();
}

void AUnitBase::CreateDecal()
{
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

void AUnitBase::SetUpCylinder()
{
	if (SelectionVolume)
	{
		SelectionVolume->SetWorldScale3D(FVector(1.0f));
		SelectionVolume->SetCollisionResponseToChannel(ECC_Camera, ECR_Block);
		SelectionVolume->OnClicked.AddDynamic(this, &IInteract::OnInteract);
	}
}

void AUnitBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

void AUnitBase::OnInteract_Implementation(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	UE_LOG(LogTemp, Warning, TEXT("Hello mother fucker"))
}
	