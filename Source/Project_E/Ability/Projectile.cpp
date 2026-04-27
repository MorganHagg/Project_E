#include "Projectile.h"

#include "DataWrappers/ChaosVDParticleDataWrapper.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Travel(DeltaTime);
}

void AProjectile::Travel(float DeltaTime)
{
	FVector Direction = (Destination - GetActorLocation()).GetSafeNormal();
	FVector NewLocation = GetActorLocation() + Direction * Speed * DeltaTime;

	SetActorLocation(NewLocation);
	SetActorRotation(Direction.Rotation());

	if (FVector::Dist(NewLocation, Destination) < 5.f)
	{
		OnFinished();
		Destroy();
	}
}

void AProjectile::SetMyAbility(UAbility* Ability)
{
	MyAbility = Ability;
}

void AProjectile::OnFinished()
{
	OnHit.ExecuteIfBound();
}
