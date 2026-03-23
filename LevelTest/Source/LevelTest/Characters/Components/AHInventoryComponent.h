#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "AHInventoryComponent.generated.h"

class AAHBaseItem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEVELTEST_API UAHInventoryComponent : public UActorComponent
{
	GENERATED_BODY()
	UAHInventoryComponent();

public:
	bool AddItemToSlot(TSubclassOf<AAHBaseItem> ItemClass, int32 Count);
	
	TSubclassOf<AAHBaseItem> GetItemData(int32 Index, int32& OutCount) const;
	
	void UpdateSlotCount(int32 Index, int32 NewCount);

protected:
	virtual void BeginPlay() override;
	
private:
	struct FSlotData {
		TSubclassOf<AAHBaseItem> ItemClass;
		int32 CurrentCount;
	};
	TArray<FSlotData> Slots; // 최대 4개 고정
	
	const int32 MaxSlots = 4;
};
