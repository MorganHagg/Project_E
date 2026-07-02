#pragma once
// Engine classes
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
// Custom classes
#include "../Misc/Stat.h"
#include "../Misc/AbilityType.h"
#include "../Interface/Damageable.h"
// Generated
#include "UnitBase.generated.h"

class UBehaviorTree;
class AAIUnit;
class UAbility;

UCLASS()
class PROJECT_E_API AUnitBase : public ACharacter, public IDamageable
{
	GENERATED_BODY()

public:
	AUnitBase();

protected:
	virtual void BeginPlay() override;
	
public:
	virtual void Tick(float DeltaTime) override;

	AAIUnit* AIController = nullptr;
	
	void SetAIController(AAIUnit* NewAIController);

	UPROPERTY(BlueprintReadWrite)
	TMap<EStat, float> Stats;
	bool GetStat(EStat Stat, float& OutValue) const;
	void ChangeStat(EStat Stat, float NewStatValue);

	UFUNCTION(BlueprintCallable)
	void MoveTo(FVector Location);
	
	UFUNCTION(BlueprintCallable)
	void SetTarget(AUnitBase* Target);
	
	UFUNCTION(BlueprintCallable)
	AUnitBase* GetTarget();

	UFUNCTION(BlueprintCallable)
	void ClearTarget();

	UPROPERTY(EditAnywhere, Category = "AI")
	UBehaviorTree* BehaviorTree;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<UAbility>> GrantedAbilities;

	UFUNCTION(BlueprintCallable)
	void AddAbility(TSubclassOf<UAbility> NewAbility);

	UFUNCTION(BlueprintCallable)
	void ReplaceAbility(TSubclassOf<UAbility> OldAbility, TSubclassOf<UAbility> NewAbility);
	
	UFUNCTION(BlueprintCallable)
	void RemoveAbility(TSubclassOf<UAbility> OldAbility);

	UFUNCTION(BlueprintCallable)
	void ActivateAbility(int AbilityIndex);
	
	void FixLocAndRot();
	
	// Interface functions
	float GetCurrentHealth();
	float GetMaxHealth();
	void ReceiveDamage(float RawDamage, EAbilityType DamageType);
	void ReceiveHeal(float RawHealing);
	void ChangeHealth(float ChangeInHealth);

	float MitigationFactor(EAbilityType DamageType);
	float AbilityFactor(EAbilityType AbilityType);

	void Die();
};