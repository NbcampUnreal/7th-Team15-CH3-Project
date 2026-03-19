#include "AHBaseConsumableItem.h"

#include "Character/AHPlayerCharacter.h"
#include "Component/AHCharacterStatusComponent.h"
#include "Kismet/GameplayStatics.h"

AAHBaseConsumableItem::	AAHBaseConsumableItem()
{
	MaxStackSize = 5; // 최대 아이템을 쌓을 수 있는 갯수
}

void AAHBaseConsumableItem::BeginPlay()
{
	Super::BeginPlay();
}

void AAHBaseConsumableItem::StartPrimeAction()
{
	AAHPlayerCharacter* Player = GetPlayerOwner();
	if (!Player) return;
	
	if (!bIsAiming) // 자가 치료
	{
		ApplyHeal(Player);
	}
	else // 아군치료
	{
		
	}
}

void AAHBaseConsumableItem::StartSecondaryAction()
{
	bIsAiming = true;
	// 누르고 있으면 아군치료하는 자세 애니메이션을 여기서 재생해야하는지 아니면 스테이트 머신에서 재정리를 해야하는지;;
}

void AAHBaseConsumableItem::EndSecondaryAction()
{
	bIsAiming = false;
}

void AAHBaseConsumableItem::ApplyHeal(AActor* Target)
{
	if (!Target) return;
	UAHCharacterStatusComponent* Status = Target->FindComponentByClass<UAHCharacterStatusComponent>();
	if (Status)
	{
		Status->Heal(HealAmount);
		
		CurrentStackSize--;
		if (CurrentStackSize <= 0)
		{
			Destroy();
		}
	}
}
