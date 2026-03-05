#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStatusComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEVELTEST_API UCharacterStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharacterStatusComponent();

	void ApplyDamage(float DamageAmount);

	FOnDeathDelegate OnDeath;

	void ResetHealth();

protected:
	virtual void BeginPlay() override;

public:	

	void Heal(float HP);

#pragma region Character Stats

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Stats")
	float MaxHP = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float CurrentHP;

#pragma endregion

/*
#pragma region State Flags

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "States")
	bool bIsSprinting = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "States")
	bool bIsAiming = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "States")
	bool bIsHiding = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "States")
	bool bIsCalmWalking = false;

#pragma endregion


#pragma region StateControl
	void SetSprinting(bool bNewState) { bIsSprinting = bNewState; }
	void SetAiming(bool bNewState) { bIsAiming = bNewState; }
	void SetHiding(bool bNewState) { bIsHiding = bNewState; }
	void SetCalmWalking(bool bNewState) { bIsCalmWalking = bNewState; }

#pragma endregion
*/
};
