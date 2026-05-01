#pragma once
// Engine classes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
// Generated
#include "StructureBase.generated.h"

UCLASS()
class PROJECT_E_API AStructureBase : public AActor
{
	GENERATED_BODY()

public:
	AStructureBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* StaticMesh;


};
