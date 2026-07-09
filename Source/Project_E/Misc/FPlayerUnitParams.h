#pragma once

#include "CoreMinimal.h"
#include "PaperZDAnimInstance.h"
#include "FPlayerUnitParams.generated.h"

USTRUCT(BlueprintType)
struct FPlayerUnitParams
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UPaperZDAnimInstance> AnimBP;
};