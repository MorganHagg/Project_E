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

	virtual int GetCurrentHealth() = 0;
	virtual int GetMaxHealth() = 0;

	virtual void ReceiveDamage(int Damage) = 0;
	virtual void ReceiveHeal(int Healing) = 0;
public:
};

/*
= 0 — must _implementation, won't compile otherwise.
No = 0, has a body — can _implementation, falls back to default if not.
No = 0, no body (BlueprintImplementableEvent) — can _implementation in Blueprint, silent no-op if not.
*/