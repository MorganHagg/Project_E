#pragma once

#include "CoreMinimal.h"
#include "Stat.generated.h"

UENUM(BlueprintType)
enum class EStat : uint8
{
	Health			UMETA(DisplayName = "Health"),
	MaxHealth		UMETA(DisplayName = "Max Health"),
	Armour			UMETA(DisplayName = "Armour"),
	MagicResist		UMETA(DisplayName = "Magic Resist"),
	Strength		UMETA(DisplayName = "Strength"),
	Intellect		UMETA(DisplayName = "Intellect"),
	Agility			UMETA(DisplayName = "Agility"),
	Range			UMETA(DisplayName = "Range")
};