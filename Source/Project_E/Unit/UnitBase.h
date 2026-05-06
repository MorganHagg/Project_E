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

// Enum
UENUM(BlueprintType)
enum class EUnitFaction : uint8
{
	Controlled,
	Hostile
};

UENUM(BlueprintType)
enum class EUnitArchetype : uint8
{
	Warrior,
	Mage,
	Ranger
};

class APlayerControls;

UCLASS()
class PROJECT_E_API AUnitBase : public ACharacter, public IDamageable
{
	GENERATED_BODY()

public:
	AUnitBase();

protected:
	virtual void BeginPlay() override;

	void CreateDecal();
	
public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Squad")
	void ToggleSelect();
	
	UFUNCTION(BlueprintCallable, Category = "Decals")
	void DrawDecal();

	UFUNCTION(BlueprintCallable, Category = "Decals")
	void RemoveDecal();

	UFUNCTION(BlueprintCallable, Category = "Decals")
	void SetDecalColor(FLinearColor Color);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decals")
	UMaterialInterface* DecalMaterial;

	UPROPERTY()
	UDecalComponent* DecalComponent;

	UPROPERTY()
	UMaterialInstanceDynamic* DecalMatInstance;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decals")
	float DecalSize = 128.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decals")
	float DecalThickness = 128.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	EUnitFaction UnitFaction = EUnitFaction::Controlled;

	APlayerControls* PlayerController = nullptr;
	AAIUnit* AIController = nullptr;
	
	void SetPlayerController();
	void SetAIController(AAIUnit* NewAIController);
	void InitFromSpawnData ();
	UPROPERTY(BlueprintReadWrite)
	TMap<EStat, float> Stats;
	bool GetStat(EStat Stat, float& OutValue) const;
	void ChangeStat(EStat Stat, float NewStatValue);
	
	UFUNCTION(BlueprintCallable)
	void SetFaction(EUnitFaction NewFaction);

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
	
	UPROPERTY(BlueprintReadWrite)
	EUnitArchetype Archetype = EUnitArchetype::Warrior;

	void SetArchetype(EUnitArchetype NewArchetype); 
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