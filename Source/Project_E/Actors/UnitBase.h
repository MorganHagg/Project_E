#pragma once
// Engine classes
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
// Custom classes
#include "../Misc/StatNames.h"
#include "../Interface/Damageable.h"
// Generated
#include "UnitBase.generated.h"

class UBehaviorTree;
class AAIBase;
class UAbility;

// Enum
UENUM(BlueprintType)
enum class EUnitFaction : uint8
{
	Controlled,
	Hostile
};

UENUM(BlueprintType)
enum class EAutoAttack : uint8
{
	Sword,
	Bow,
	Staff
};

class AControllerBase;

UCLASS()
class PROJECT_E_API AUnitBase : public ACharacter, public IDamageable
{
	GENERATED_BODY()

public:
	AUnitBase();
	virtual void PreInitializeComponents() override;

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
	EUnitFaction UnitType = EUnitFaction::Controlled;

	AControllerBase* PlayerController = nullptr;
	AAIBase* AIController = nullptr;
	
	void SetPlayerController();
	void SetAIController(AAIBase* NewAIController);
	void InitStats();
	UPROPERTY(BlueprintReadWrite)
	TMap<EStat, int> Stats;
	bool GetStat(EStat Stat, int& OutValue) const;
	void ChangeStat(EStat Stat, int NewStatValue);
	
	UFUNCTION(BlueprintCallable)
	void SetUnitType(EUnitFaction NewType);

	void MoveTo(FVector Location);

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
	
	

	// Interface functions
	int GetCurrentHealth();
	int GetMaxHealth();
	void ReceiveDamage(int Damage);
	void ReceiveHeal(int Healing);
	void ChangeHealth(int ChangeInHealth);

	void Die();

	UPROPERTY(BlueprintReadOnly)
	EAutoAttack AutoAttack = EAutoAttack::Sword;

	UFUNCTION(BlueprintCallable)
	void ChangeWeapon(EAutoAttack NewType);
};