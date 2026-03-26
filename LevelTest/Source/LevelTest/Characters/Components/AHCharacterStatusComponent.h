#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AHCharacterStatusComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LEVELTEST_API UAHCharacterStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAHCharacterStatusComponent();

	void ApplyDamage(float DamageAmount);
	void Heal(float HP);
	void ResetHealth();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MaxHP = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float CurrentHP;

protected:
	virtual void BeginPlay() override;

private:
};