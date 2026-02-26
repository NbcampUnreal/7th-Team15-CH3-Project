#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UsableItemInterface.generated.h"

UINTERFACE(MinimalAPI)
class UUsableItemInterface : public UInterface
{
	GENERATED_BODY()
};

class LEVELTEST_API IUsableItemInterface
{
	GENERATED_BODY()
public:

#pragma region Input Mapping Actions
	virtual void PrimaryAction() = 0;

	virtual void SecondaryAction(bool bIsStarting) = 0;

	virtual void ReloadAction() = 0;
#pragma endregion

#pragma region Item Info
	virtual FString GetItemName() const = 0;
#pragma endregion

};
