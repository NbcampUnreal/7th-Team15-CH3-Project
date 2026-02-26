#include "CharacterStatusComponent.h"

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