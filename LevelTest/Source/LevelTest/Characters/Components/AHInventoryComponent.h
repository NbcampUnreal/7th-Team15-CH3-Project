#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "AHInventoryComponent.generated.h"

class AAHBaseItem;
class UAHItemData;

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAHItemData* ItemData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentCount;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag ItemTag;
	
	FInventorySlot() : ItemData(nullptr), CurrentCount(0) {}
};
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEVELTEST_API UAHInventoryComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UAHInventoryComponent();
	
	UFUNCTION(BlueprintCallable)
	bool AddItemToSlot(UAHItemData* NewItemData, int32 Count);
	
	UFUNCTION(BlueprintPure, Category = "Inventory")
	bool GetSlotInfo(int32 Index, UAHItemData*& OutData, int32& OunCount) const;
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void EquipItemFromSlot(int32 SlotIndex);
	
	//번호(1~4)를 통한 장착 요청 
	void RequestEquipByIndex(int32 SlotIndex);

	// 슬롯 수량 업데이트 및 비우기 처리 
	void UpdateSlotCount(int32 Index, int32 NewCount);
	
	bool CheckItemByTag(FGameplayTag Tag);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<FInventorySlot> Slots;
	
	const int32 MaxSlots = 4;
	// 서브시스템 호출용 헬퍼
	void NotifySlotUpdate(int32 Index);
	
	
};
