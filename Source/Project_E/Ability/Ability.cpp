#include "Ability.h"
#include "../Actors/UnitBase.h"
#include "Projectile.h"
#include "SAdvancedTransformInputBox.h"

UAbility::UAbility()
{
	
}

void UAbility::Initiate(AUnitBase* Owner)
{
	MyOwner = Owner;

	if (!MyOwner)
	{
		UE_LOG(LogTemp, Error, TEXT("Missing Owner"));
		EndAbility();
		return;
	}
	World = MyOwner->GetWorld();
	Activate();
}

void UAbility::Activate_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("%s has no Activate implementation"), *GetName());
}

void UAbility::EndAbility()
{
	MyOwner = nullptr;
	MyTarget = nullptr;
}

void UAbility::RunEffect_Projectile(FLatentActionInfo LatentInfo, UStaticMesh* Mesh, FVector Target, float Speed)
{
	if (!MyOwner || !World) return;

	FLatentActionManager& LAM = World->GetLatentActionManager();
	FEffect_ProjectileAction* Action = new FEffect_ProjectileAction(LatentInfo);
	LAM.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);

	AProjectile* Projectile = World->SpawnActor<AProjectile>(
		AProjectile::StaticClass(),
		MyOwner->GetActorLocation(),
		MyOwner->GetActorRotation()
	);
	Projectile->SetMyAbility(this);
	Projectile->Destination = Target;
	Projectile->Speed = Speed;

	if (Mesh)
		Projectile->MeshComponent->SetStaticMesh(Mesh);

	TWeakObjectPtr<UAbility> WeakThis = this;
	Projectile->OnHit.BindLambda([WeakThis, Action]()
	{
		if (WeakThis.IsValid())
			Action->bComplete = true;
	});
}


void UAbility::RunEffect_Damage()
{
}

void UAbility::RunEffect_Heal()
{
}

void UAbility::RunEffect_AOE()
{
	
}

void UAbility::RunEffect_ApplyStasis()
{
	
}

AActor* UAbility::RunEffect_SpawnObject(AActor* SpawnActor, FVector SpawnLocation)
{
	AActor* SpawnedActor = World->SpawnActor<AActor>(
	AActor::StaticClass(),
	SpawnLocation,
	SpawnParams.Owner->GetActorRotation(),
	SpawnParams	);
	
	return SpawnedActor;
}
