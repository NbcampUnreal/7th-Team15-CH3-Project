#include "CharacterStatusComponent.h"
#include "APlayerCharacter.h"

UCharacterStatusComponent::UCharacterStatusComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	MaxHP = 100.f;

	CurrentHP = MaxHP;

}


void UCharacterStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHP = MaxHP;
}

void UCharacterStatusComponent::Heal(float HP)
{
	if (CurrentHP >= MaxHP)return;

	CurrentHP = FMath::Clamp(CurrentHP + HP, 0.f, MaxHP);

	if (AAPlayerCharacter* OwnerChar = Cast<AAPlayerCharacter>(GetOwner()))
	{
		// 이전에 만들어둔 심박수 업데이트 함수 활용
		float HealthPercent = CurrentHP / MaxHP;

		UE_LOG(LogTemp, Warning, TEXT("Healed! Current HP: %f"), CurrentHP);
	}
}

void UCharacterStatusComponent::ApplyDamage(float DamageAmount)
{

	if (DamageAmount <= 0.f || CurrentHP <= 0.f)return;

	CurrentHP = FMath::Clamp(CurrentHP - DamageAmount, 0.f, MaxHP);

	UE_LOG(LogTemp, Log, TEXT("DamageTest Check"));

	if (FMath::IsNearlyZero(CurrentHP))
	{
		if (OnDeath.IsBound()) // 델리게이트 크래시 방지용
		{
			OnDeath.Broadcast();
			UE_LOG(LogTemp, Warning, TEXT("Dead Check"));
		}
	}
}

void UCharacterStatusComponent::ResetHealth()
{
	CurrentHP = MaxHP;
}

void UCombatComponent::AddKey(FGameplayTag KeyTag)
{
	if (!KeyTag.IsValid()) return;

	OwnedKeys.AddUnique(KeyTag);

	UE_LOG(LogTemp, Warning, TEXT("Key Acquired: %s"), *KeyTag.ToString());
}

bool UCombatComponent::HasKey(FGameplayTag KeyTag) const
{
	return OwnedKeys.Contains(KeyTag);
}

void UCombatComponent::RemoveKey(FGameplayTag KeyTag)
{
	OwnedKeys.Remove(KeyTag);
}