#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractInterface.generated.h"

UINTERFACE(MinimalAPI)
class UInteractInterface : public UInterface
{
	GENERATED_BODY()
};

class LEVELTEST_API IInteractInterface
{
	GENERATED_BODY()

public:
	virtual void Interact(AActor* Interactor) = 0;

	//virtual FString GetInteractText() const { return TEXT("상호작용 (E)"); }
};
