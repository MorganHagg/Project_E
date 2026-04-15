// Engine classes
#include "UnitBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "../Input/ControllerBase.h"

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
		SelectionVolume->SetCollisionResponseToChannel(ECC_Camera, ECR_Block);
	}
}

void AUnitBase::BeginPlay()
{
	Super::BeginPlay();
	CreateDecal();
	SetUpCylinder();
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

// Adjusts SelectionCylinder's height to be 5% larger than CapsuleComponent
void AUnitBase::SetUpCylinder()
{
	if (SelectionVolume)
	{
		// Add OnClicked input
		SelectionVolume->OnClicked.AddDynamic(this, &IInteract::OnInteract);
		// Get CapsuleComponent's height
		float CapsuleHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * 2.f;
		// Get SelectionVolume's height
		float CylinderHeight = SelectionVolume->GetStaticMesh()->GetBounds().BoxExtent.Z * 2.0f;
		// Z.Scale multiplier
		float ZScaleMultiplier = 1.05f;

		// Calculate scale
		float ZScale = CapsuleHeight / CylinderHeight;
		FVector XZSize = SelectionVolume->GetRelativeScale3D();
		FVector NewScale = FVector(XZSize.X, XZSize.Y, ZScale * ZScaleMultiplier);

		// Apply new scale and making sure SelectionVolume is in the correct location
		SelectionVolume->SetWorldScale3D(NewScale);
		SelectionVolume->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
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
	UE_LOG(LogTemp, Warning, TEXT("Someone touched me"))
	switch (UnitType)
	{
		case EUnitType::Controlled:
		if (Controller)
		{
			Controller->ClearSelectedUnits();
			Controller->AddUnit(this);
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("Commander is not valid"));
		break;

		case EUnitType::Friendly:
		break;

		case EUnitType::Hostile:
		break;
	}
}

void AUnitBase::SetController()
{
	Controller = Cast<AControllerBase>(GetWorld()->GetFirstPlayerController());
}
	