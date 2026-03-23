#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Commander.generated.h"

UCLASS()
class PROJECT_E_API ACommander : public APawn
{
	GENERATED_BODY()

public:
	ACommander();
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

};