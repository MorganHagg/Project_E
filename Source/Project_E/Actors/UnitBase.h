#pragma once
// Engine classes
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
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

class AControllerBase;

UCLASS()
class PROJECT_E_API AUnitBase : public ACharacter
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

	AControllerBase* Controller = nullptr;
	AAIBase* MyController = nullptr;
	
	void SetController();
	
	UFUNCTION(BlueprintCallable)
	void SetUnitType(EUnitFaction NewType);

	void Attack();
	void MoveTo(FVector Location);

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
	
	AUnitBase* MyTarget;

	UFUNCTION(BlueprintCallable)
	AUnitBase* GetMyTarget() {return MyTarget;};
};