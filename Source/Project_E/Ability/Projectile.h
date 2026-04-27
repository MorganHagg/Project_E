#pragma once
// Engine classes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
// Generated
#include "Projectile.generated.h"

class UAbility;

DECLARE_DELEGATE(FOnProjectileHit);

UCLASS()
class PROJECT_E_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	AProjectile();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void Travel(float DeltaTime);
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;

	UFUNCTION()
	void SetMyAbility(UAbility* Ability);
	UPROPERTY(VisibleAnywhere)
	UAbility* MyAbility;
	
	FVector Destination;
	float Speed;
	int TaskID;
	void OnFinished();
	
	FOnProjectileHit OnHit;
};
