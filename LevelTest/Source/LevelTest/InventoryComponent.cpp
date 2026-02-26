#include "InventoryComponent.h"
#include"UsableItemInterface.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryComponent::UseEquippedItem()
{
	if (!CurrentEquippedItem) return;

	IUsableItemInterface* Usable = Cast<IUsableItemInterface>(CurrentEquippedItem);
	if (Usable)
	{
		Usable->PrimaryAction();
	}
}

void UInventoryComponent::ReloadItem()
{
	if (!CurrentEquippedItem) return;

	IUsableItemInterface* Usable = Cast<IUsableItemInterface>(CurrentEquippedItem);
	if (Usable)
	{
		Usable->ReloadAction();
	}
}

void UInventoryComponent::EquipItem(AActor* NewItem)
{
	if (!NewItem) return;

	CurrentEquippedItem = NewItem;
}