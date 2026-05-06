// Engine classes
#include "Ability.h"
#include "Projectile.h"
#include "SAdvancedTransformInputBox.h"
#include "Engine/OverlapResult.h"
// Custom classes
#include "../Component/UnitHandler.h"
#include "../Unit/UnitBase.h"

UAbility::UAbility()
{
	
}

void UAbility::Initiate(AUnitBase* Owner)
{
	MyOwner = Owner;
	if (!MyOwner) { EndAbility(); return; }
	World = MyOwner->GetWorld();
	Activate(MyOwner, MyOwner->AIController);
}

void UAbility::Activate_Implementation(AUnitBase* Owner, AAIUnit* AIController)
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
	FEffect_ProjectileAction* ProjectileAction = new FEffect_ProjectileAction(LatentInfo);
	LAM.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, ProjectileAction);

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
	Projectile->OnHit.BindLambda([WeakThis, ProjectileAction]()
	{
		if (WeakThis.IsValid())
			ProjectileAction->bComplete = true;
	});
}


void UAbility::RunEffect_Damage(AUnitBase* Target, int RawDamage, EAbilityType DamageType)
{
	Target->ReceiveDamage(RawDamage, DamageType);
}

void UAbility::RunEffect_Heal(AUnitBase* Target, int RawHealing)
{
	Target->ReceiveHeal(RawHealing);
}

TArray<AUnitBase*> UAbility::RunEffect_AOE(FVector Location, float Radius, ETargetSelection TargetSelection)
{
	TArray<AUnitBase*> Targets;
	TArray<FOverlapResult> Overlaps;

	FCollisionShape Sphere = FCollisionShape::MakeSphere(Radius);
	FCollisionQueryParams Params;
	
	if (World->OverlapMultiByChannel(Overlaps, Location, FQuat::Identity, ECC_Pawn, Sphere, Params) && MyOwner->MyHandler)
		for (FOverlapResult& Overlap : Overlaps)
		{
			AUnitBase* Unit = Cast<AUnitBase>(Overlap.GetActor());
			if (!Unit) continue;

			if (TargetSelection == ETargetSelection::All ||
			   (TargetSelection == ETargetSelection::Friendly && MyOwner->MyHandler->IsInSquad(Unit)) ||
			   (TargetSelection == ETargetSelection::Hostile && !MyOwner->MyHandler->IsInSquad(Unit)))
			{
				Targets.AddUnique(Unit);
			}
		}
	return Targets;
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
