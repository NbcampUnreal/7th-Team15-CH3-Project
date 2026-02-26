#include "AHInventoryComponent.h"

#include "Actor/Character/Interface/AHUsableItemInterface.h"

UAHInventoryComponent::UAHInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UAHInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UAHInventoryComponent::UseEquippedItem()
{
	if (!CurrentEquippedItem) return;

	IAHUsableItemInterface* Usable = Cast<IAHUsableItemInterface>(CurrentEquippedItem);
	if (Usable)
	{
		Usable->PrimaryAction();
	}
}

void UAHInventoryComponent::ReloadItem()
{
	if (!CurrentEquippedItem) return;

	IAHUsableItemInterface* Usable = Cast<IAHUsableItemInterface>(CurrentEquippedItem);
	if (Usable)
	{
		Usable->ReloadAction();
	}
}

void UAHInventoryComponent::EquipItem(AActor* NewItem)
{
	if (!NewItem) return;

	CurrentEquippedItem = NewItem;
}