#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AHCharacterStatusComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathDelegate);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LEVELTEST_API UAHCharacterStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAHCharacterStatusComponent();

	void ApplyDamage(float DamageAmount);
	void Heal(float HP);
	void ResetHealth();
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDeathDelegate OnDeath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MaxHP = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float CurrentHP;

protected:
	virtual void BeginPlay() override;

private:
};