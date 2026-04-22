#include "Ability.h"
#include "../Actors/UnitBase.h"
#include "Projectile.h"
#include "SAdvancedTransformInputBox.h"

void UAbility::Activate_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("%s has no Activate implementation"), *GetName());
}

UAbility::UAbility()
{
	if (GetOwner())
	{
		SpawnParams.Owner = GetOwner();
		//MyTarget = GetOwner()->MyTarget;
		World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Missing Owner or Target"));
		EndAbility();
	}
}

AUnitBase* UAbility::GetOwner()
{
	return Cast<AUnitBase>(GetOuter());
}

void UAbility::EndAbility()
{
	MarkAsGarbage();
}

void UAbility::RunEffect_Projectile(FLatentActionInfo LatentInfo, UStaticMesh* Mesh, FVector Target, float Speed)
{
	if (!GetOwner())
		return;
	FLatentActionManager& LAM = World->GetLatentActionManager();
	FEffect_ProjectileAction* Action = new FEffect_ProjectileAction(LatentInfo);
	LAM.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);

	AProjectile* Projectile = World->SpawnActor<AProjectile>(
		AProjectile::StaticClass(),
		SpawnParams.Owner->GetActorLocation(),
		SpawnParams.Owner->GetActorRotation(),
		SpawnParams	);
	
	Projectile->Destination = Target;
	Projectile->Speed = Speed;
	if (Mesh)
		Projectile->MeshComponent->SetStaticMesh(Mesh);
	else
		UE_LOG(LogTemp, Warning, TEXT("Ability is missing mesh!"))

	// Bind delegation
	Projectile->OnHit.BindLambda([Action]()
		{	Action->bComplete = true;	}
	);
		
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
