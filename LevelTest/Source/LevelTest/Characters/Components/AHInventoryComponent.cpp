#include "Characters/Components/AHInventoryComponent.h"
#include "Subsystem/AHGameInstanceSubsystem.h"
#include "Actors/AHBaseItem.h"

UAHInventoryComponent::UAHInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAHInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
	//Slots.Init(FInventoryData(), MaxSlots);
}


bool UAHInventoryComponent::AddItemToSlot(TSubclassOf<AAHBaseItem> ItemClass, int32 Count)
{
	if (ItemClass == nullptr) return false;
	
	for (int32 i = 0; i <  MaxSlots; i++)
	{
		if (Slots[i].ItemClass == nullptr || Slots[i].ItemClass == ItemClass)
		{
			if (Slots[i].ItemClass == nullptr)
			{
				Slots[i].ItemClass = ItemClass;
				Slots[i].CurrentCount = Count;
			}
			else if (Slots[i].ItemClass == ItemClass)
			{
				Slots[i].CurrentCount += Count;
			}
			if (UAHGameInstanceSubsystem* GISub = GetWorld()->GetGameInstance()->GetSubsystem<UAHGameInstanceSubsystem>())
			{
				GISub->OnSlotUpdated.Broadcast(i, ItemClass, Count);
			}
			return true;
		}
	}
	return false;
	
}
