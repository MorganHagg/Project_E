#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Stat.h"
#include "StatStruct.generated.h"

USTRUCT(BlueprintType)
struct FStatStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EStat, int32> Stats = {
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
