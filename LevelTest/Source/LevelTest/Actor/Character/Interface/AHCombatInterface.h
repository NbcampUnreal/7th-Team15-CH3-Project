#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AHCombatInterface.generated.h"

UINTERFACE(MinimalAPI)
class UAHCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class LEVELTEST_API IAHCombatInterface
{
	GENERATED_BODY()

public:

	virtual void GetDamage(float DamageAmount) = 0;
};
