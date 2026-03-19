#include "Component/AHCharacterStatusComponent.h"
#include "Character/AHPlayerCharacter.h" 

// --- Constructor & Lifecycle ---

UAHCharacterStatusComponent::UAHCharacterStatusComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	MaxHP = 100.f;
	CurrentHP = MaxHP;
}

void UAHCharacterStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHP = MaxHP;
}

// --- Public Methods ---

void UAHCharacterStatusComponent::ApplyDamage(float DamageAmount)
{
	if (DamageAmount <= 0.f || CurrentHP <= 0.f) return;

	CurrentHP = FMath::Clamp(CurrentHP - DamageAmount, 0.f, MaxHP);

	UE_LOG(LogTemp, Log, TEXT("Damage Received. Current HP: %f"), CurrentHP);

	if (FMath::IsNearlyZero(CurrentHP))
	{
		if (OnDeath.IsBound())
		{
			OnDeath.Broadcast();
			UE_LOG(LogTemp, Warning, TEXT("Character is Dead"));
		}
	}
}

void UAHCharacterStatusComponent::Heal(float HP)
{
	if (CurrentHP >= MaxHP) return;

	CurrentHP = FMath::Clamp(CurrentHP + HP, 0.f, MaxHP);

	// 플레이어 캐릭터인 경우 UI 처리를 위한 로직 (필요 시 BaseCharacter로 확장 가능)
	if (AAHPlayerCharacter* OwnerChar = Cast<AAHPlayerCharacter>(GetOwner()))
	{
		float HealthPercent = CurrentHP / MaxHP;
		// 여기에 심박수 UI 업데이트 등 추가 로직 연결 가능
        
		UE_LOG(LogTemp, Warning, TEXT("Healed! Current HP: %f"), CurrentHP);
	}
}

void UAHCharacterStatusComponent::ResetHealth()
{
	CurrentHP = MaxHP;
	UE_LOG(LogTemp, Log, TEXT("Health Reset to Max"));
}