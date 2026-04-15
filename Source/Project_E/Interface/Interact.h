#pragma once
// Engine classes
#include "CoreMinimal.h"
#include "UObject/Interface.h"
// Generated
#include "Interact.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInteract : public UInterface
{
	GENERATED_BODY()
};

class PROJECT_E_API IInteract
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
	void OnInteract(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	
};
