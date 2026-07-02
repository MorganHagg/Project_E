#pragma once

#include "CoreMinimal.h"
#include "FPlayerUnitParams.generated.h"

USTRUCT(BlueprintType)
struct FPlayerUnitParams
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString Name;

	UPROPERTY(BlueprintReadWrite)
	USkeletalMesh* Mesh;
};