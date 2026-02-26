#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AHInteractInterface.generated.h"

UINTERFACE(MinimalAPI)
class UAHInteractInterface : public UInterface
{
	GENERATED_BODY()
};

class LEVELTEST_API IAHInteractInterface
{
	GENERATED_BODY()

public:
	virtual void Interact(AActor* Interactor) = 0;

	//virtual FString GetInteractText() const { return TEXT("상호작용 (E)"); }
};
