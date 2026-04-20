
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PlayerAIBase.generated.h"

UCLASS()
class PROJECT_E_API APlayerAIBase : public AAIController
{
	GENERATED_BODY()
	
public:
	APlayerAIBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

};