#pragma once
// Engine classes
#include "CoreMinimal.h"
// Generated
#include "Damageable.generated.h"

UINTERFACE()
class UDamageable : public UInterface
{
	GENERATED_BODY()
};

class PROJECT_E_API IDamageable
{
	GENERATED_BODY()

	int Getheath();

	void TakeDamage(int damage);
	void GetHealth(int health);
public:
};

/*
= 0 — must _implementation, won't compile otherwise.
No = 0, has a body — can _implementation, falls back to default if not.
No = 0, no body (BlueprintImplementableEvent) — can _implementation in Blueprint, silent no-op if not.
*/