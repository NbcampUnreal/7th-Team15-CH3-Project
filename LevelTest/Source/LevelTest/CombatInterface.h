#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

UINTERFACE(MinimalAPI)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class LEVELTEST_API ICombatInterface
{
	GENERATED_BODY()

public:

	virtual void GetDamage(float DamageAmount) = 0;
};
