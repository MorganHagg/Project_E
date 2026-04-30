#pragma once
// Engine classes
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Engine/LatentActionManager.h"
// Generated classes
#include "Ability.generated.h"

// Forward declarations
class AProjectile;
class AUnitBase;
class UActionManager;

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

	void Initiate(AUnitBase* Owner);
	
	UFUNCTION(BlueprintNativeEvent)
	void Activate();

	UFUNCTION(BlueprintCallable)
	void EndAbility();

	UFUNCTION(BlueprintCallable, meta=(Latent, LatentInfo="LatentInfo"), Category="Ability")
	void RunEffect_Projectile(FLatentActionInfo LatentInfo, UStaticMesh* Mesh, FVector Target, float Speed);
	
	UFUNCTION(BlueprintCallable, Category="Ability")
	void RunEffect_Damage();

	UFUNCTION(BlueprintCallable, Category="Ability")
	void RunEffect_Heal();

	UFUNCTION(BlueprintCallable, Category="Ability")
	void RunEffect_AOE();

	UFUNCTION(BlueprintCallable, Category="Ability")
	void RunEffect_ApplyStasis();

	UFUNCTION(BlueprintCallable, Category="Ability")
	AActor* RunEffect_SpawnObject(AActor* SpawnActor, FVector SpawnLocation);

	UPROPERTY(BlueprintReadOnly)
	float CoolDown = 0.f;
};
