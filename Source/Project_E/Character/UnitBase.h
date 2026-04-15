#pragma once
// Engine classes
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
// Custom classes
#include "../Interface/Interact.h"
// Generated
#include "UnitBase.generated.h"

UCLASS()
class PROJECT_E_API AUnitBase : public ACharacter, public IInteract
{
	GENERATED_BODY()

public:
	AUnitBase();


protected:
	virtual void BeginPlay() override;

	void CreateDecal();

	void SetUpCylinder();
	
public:
	virtual void Tick(float DeltaTime) override;

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

	UFUNCTION()
	virtual void OnInteract_Implementation(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SelectionVolume;
};