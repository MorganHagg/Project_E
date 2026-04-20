#include "StructureBase.h"
#include "Components/StaticMeshComponent.h"

AStructureBase::AStructureBase()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	SetRootComponent(StaticMesh); 
}

void AStructureBase::BeginPlay()
{
	Super::BeginPlay();
}

void AStructureBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
