#include "AHBaseConsumableItem.h"

#include"Characters/Player/AHPlayerCharacter.h"
#include "Characters/Components/AHCharacterStatusComponent.h"


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
	// 1. AHPlayerCharacter를 AAHPlayerCharacter로 수정
	AAHPlayerCharacter* Player = GetPlayerOwner(); 
	if (!Player) return;
    
	if (!bIsAiming) // 자가 치료
	{
		// 나 자신(Player)을 Target으로 넘김
		ApplyHeal(Player);
	}
	else // 아군 치료
	{
		// 
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
	// 2. 매개변수로 받은 Target이 유효한지 확인
	if (!Target) return;

	// 3. Target에서 상태 컴포넌트를 직접 찾아 치료 (이 방식이 더 범용적입니다)
	UAHCharacterStatusComponent* Status = Target->FindComponentByClass<UAHCharacterStatusComponent>();
    
	// 만약 클래스 구조상 StatusComp에 직접 접근해야 한다면 캐스팅을 활용:
	// AAHPlayerCharacter* TargetPlayer = Cast<AAHPlayerCharacter>(Target);
	// if (TargetPlayer && TargetPlayer->StatusComp) { ... }

	if (Status)
	{
		Status->Heal(40.f); // 혹은 설정된 HealAmount 사용
       
		CurrentStackSize--;
		if (CurrentStackSize <= 0)
		{
			Destroy();
		}
	}
}
