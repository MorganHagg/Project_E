#pragma once

UENUM(BlueprintType)
enum class EAction : uint8
{
	Walking		UMETA(DisplayName = "Walking"),
	Attacking	UMETA(DisplayName = "Attacking")
};