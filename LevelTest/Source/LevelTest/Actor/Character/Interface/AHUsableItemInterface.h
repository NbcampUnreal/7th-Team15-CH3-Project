#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AHUsableItemInterface.generated.h"

UINTERFACE(MinimalAPI)
class UAHUsableItemInterface : public UInterface
{
	GENERATED_BODY()
};

class LEVELTEST_API IAHUsableItemInterface
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
