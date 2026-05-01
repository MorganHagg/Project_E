 #pragma once
// Engine classes
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
// Generated
#include "AICommander.generated.h"

UCLASS()
class PROJECT_E_API AAICommander : public APawn
{
	GENERATED_BODY()

public:
	AAICommander();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
