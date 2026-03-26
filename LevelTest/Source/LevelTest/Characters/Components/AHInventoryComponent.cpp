#include "Characters/Components/AHInventoryComponent.h"
#include "Subsystem/EventSubsystem.h"
#include "Actors/AHBaseItems/AHBaseItem.h"
#include "AHItemData.h"
#include "CookPackageSplitter.h"
#include "Algo/Count.h"

UAHInventoryComponent::UAHInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAHInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
	//TArray<FInventoryData> 타입 배열, .Init()은 배열크기 지정, 해당요소를 특정 값으로 채우기,
	//배열 각 칸을 채울 초기 데이터를 빈 아이템 상태로 초기화,, NUmber 는 슬롯 갯수
	Slots.Init(FInventorySlot(), MaxSlots);
}

bool UAHInventoryComponent::AddItemToSlot(UAHItemData* NewItemData, int32 Count)
{
	if (!NewItemData) return false;

	// 1. 이미 같은 아이템 에셋이 있는지 확인 (중첩)
	for (int32 i = 0; i < MaxSlots; i++)
	{
		if (Slots[i].ItemData == NewItemData)
		{
			Slots[i].CurrentCount += Count;
			NotifySlotUpdate(i);
			return true;
		}
	}
	// 2. 빈 자리 찾기
	for (int32 i = 0; i < MaxSlots; i++)
	{
		if (Slots[i].ItemData == nullptr)
		{
			Slots[i].ItemData = NewItemData;
			Slots[i].CurrentCount = Count;
			NotifySlotUpdate(i);
			return true;
		}
	}

	return false; // 가득 참
}

bool UAHInventoryComponent::GetSlotInfo(int32 Index, UAHItemData*& OutData, int32& OutCount) const
{
	if (Slots.IsValidIndex(Index) && Slots[Index].ItemData)
	{
		OutData = Slots[Index].ItemData;
		OutCount = Slots[Index].CurrentCount;
		return true;
	}
	return false;
}

void UAHInventoryComponent::RequestEquipByIndex(int32 SlotIndex)
{
	int32 TargetIndex = SlotIndex - 1; // 1번 입력시  0번 인덱스로 받기

	if (Slots.IsValidIndex(TargetIndex) ==false || Slots[TargetIndex].ItemData == nullptr)
	{
		return;
	}
	// 서브시스템을 통해 방송 (캐릭터가 이 정보를 받아 장착)
	if (UEventSubsystem* EventSys = UEventSubsystem::Get(this))
	{
		// 델리게이트 매개변수를 UAHItemData*를 받도록 수정해야 함
		EventSys->OnEquipFromSlot.Broadcast(TargetIndex); 
	}
}

void UAHInventoryComponent::UpdateSlotCount(int32 Index, int32 NewCount)
{
	if (Slots.IsValidIndex(Index) == false)
	{
		return;
	}
	Slots[Index].CurrentCount = FMath::Max(0,NewCount);
	if (Slots[Index].CurrentCount == 0)
	{
		Slots[Index].ItemData = nullptr;
	}
	NotifySlotUpdate(Index);

}

void UAHInventoryComponent::NotifySlotUpdate(int32 Index)
{
	if (UEventSubsystem* EventSys = UEventSubsystem::Get(this))
	{
		TSubclassOf<AAHBaseItem> ItemClass = Slots[Index].ItemData ? Slots[Index].ItemData->ItemClass : nullptr;
		EventSys->OnSlotUpdated.Broadcast(Index, ItemClass, Slots[Index].CurrentCount);
	}
}

bool UAHInventoryComponent::CheckItemByTag(FGameplayTag SearchingTag)
{
	// 1. 이미 같은 아이템 에셋이 있는지 확인 (중첩)
	for (int32 i = 0; i < MaxSlots; i++)
	{
		if (Slots[i].ItemTag == SearchingTag)
		{
			Slots[i].ItemData = nullptr;
			NotifySlotUpdate(i);
			return true;
		}
	}
	return false;
}

