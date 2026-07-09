#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Stat.h"
#include "PaperZDAnimInstance.h"
#include "FUnitSpawnDataRow.generated.h"

USTRUCT(BlueprintType)
struct FFUnitSpawnDataRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UPaperZDAnimInstance> AnimBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBehaviorTree* BehaviorTree = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<UAbility>> DefaultAbilities;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EStat, float> Stats = {
		{ EStat::Health, 100 },
		{ EStat::MaxHealth, 100 },
		{ EStat::Armour, 100 },
		{ EStat::MagicResist, 100 }, 
		{ EStat::Strength, 10 },
		{ EStat::Agility, 10 },
		{ EStat::Intellect, 10 },
		{ EStat::Range, 100 }
	};
};
