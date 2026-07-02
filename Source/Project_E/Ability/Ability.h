#pragma once
// Engine classes
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Engine/LatentActionManager.h"
// Custom classes
#include "../Misc/AbilityType.h"
// Generated classes
#include "Ability.generated.h"

// Forward declarations
class AProjectile;
class AUnitBase;
class UActionManager;
class APlayerControls;

// Enum
UENUM(BlueprintType)
enum class ETargetSelection : uint8
{
	Friendly,
	Hostile,
	All
};

// Effects
class FEffect_ProjectileAction : public FPendingLatentAction
{
public:
	FName ExecutionFunction;
	int32 OutputLink;
	FWeakObjectPtr CallbackTarget;
	bool bComplete = false;

	FEffect_ProjectileAction(const FLatentActionInfo& Info)
		: ExecutionFunction(Info.ExecutionFunction)
		, OutputLink(Info.Linkage)
		, CallbackTarget(Info.CallbackTarget)
	{}

	virtual void UpdateOperation(FLatentResponse& Response) override
	{
		Response.FinishAndTriggerIf(bComplete, ExecutionFunction, OutputLink, CallbackTarget);
	}
};

UCLASS(Blueprintable)
class PROJECT_E_API UAbility : public UObject
{
	GENERATED_BODY()
	UAbility();

public:
	UPROPERTY(BlueprintReadOnly)
	AUnitBase* MyOwner;
	
	UPROPERTY(BlueprintReadWrite)
	AUnitBase* MyTarget;

	UWorld* World;
	FActorSpawnParameters SpawnParams;

	APlayerControls* MyController;

	void Initiate(AUnitBase* Owner);
	
	UFUNCTION(BlueprintNativeEvent)
	void Activate(AUnitBase* Owner, AAIUnit* AIController);

	UFUNCTION(BlueprintCallable)
	void EndAbility();

	UFUNCTION(BlueprintCallable, meta=(Latent, LatentInfo="LatentInfo"), Category="Ability")
	void RunEffect_Projectile(FLatentActionInfo LatentInfo, UStaticMesh* Mesh, FVector Target, float Speed);
	
	UFUNCTION(BlueprintCallable, Category="Ability")
	void RunEffect_Damage(AUnitBase* Target, int RawDamage, EAbilityType DamageType);

	UFUNCTION(BlueprintCallable, Category="Ability")
	void RunEffect_Heal(AUnitBase* Target, int RawHealing);

	UFUNCTION(BlueprintCallable, Category="Ability")
	TArray<AUnitBase*> RunEffect_AOE(FVector Location, float Radius, ETargetSelection TargetSelection);

	UFUNCTION(BlueprintCallable, Category="Ability")
	void RunEffect_ApplyStasis();

	UFUNCTION(BlueprintCallable, Category="Ability")
	AActor* RunEffect_SpawnObject(AActor* SpawnActor, FVector SpawnLocation);

	UPROPERTY(BlueprintReadOnly)
	float CoolDown = 0.f;
};
