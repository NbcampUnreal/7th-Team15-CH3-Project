#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AHCharacterStatusComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEVELTEST_API UAHCharacterStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAHCharacterStatusComponent();
	
protected:
	virtual void BeginPlay() override;
	
public:
	void ApplyDamage(float DamageAmount);
	void ResetHealth();

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Stats")
	float MaxHP = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float CurrentHP;
	
	FOnDeathDelegate OnDeath;
};