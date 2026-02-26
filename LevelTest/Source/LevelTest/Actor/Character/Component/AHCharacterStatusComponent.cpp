#include "AHCharacterStatusComponent.h"

UAHCharacterStatusComponent::UAHCharacterStatusComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAHCharacterStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHP = MaxHP;
}

void UAHCharacterStatusComponent::ApplyDamage(float DamageAmount)
{
	if (DamageAmount <= 0.f || CurrentHP <= 0.f)
	{
		return;
	}

	CurrentHP = FMath::Clamp(CurrentHP - DamageAmount, 0.f, MaxHP);

	UE_LOG(LogTemp, Log, TEXT("DamageTest Check"));

	if (CurrentHP <= 0.f)
	{
		if (OnDeath.IsBound()) // 델리게이트 크래시 방지용
		{
			OnDeath.Broadcast();
		}
		
		UE_LOG(LogTemp, Warning, TEXT("Dead Check"));
	}
}

void UAHCharacterStatusComponent::ResetHealth()
{
	CurrentHP = MaxHP;
}