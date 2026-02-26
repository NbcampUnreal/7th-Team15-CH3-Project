#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

class ABaseWeapon;
class AAPlayerCharacter;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LEVELTEST_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCombatComponent();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<TSubclassOf<class ABaseWeapon>> QuickbarSlots;

	void AddWeaponToQuickbar(TSubclassOf<ABaseWeapon> WeaponClass);

	void SwitchWeapon(int32 SlotIndex);

	void ProcessPrimaryAction();

	void ProcessSecondaryAction(bool bIsPressed);

	void EquipWeapon(ABaseWeapon* WeaponToEquip);

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<ABaseWeapon> DefaultWeaponClass;

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	ABaseWeapon* EquippedWeapon;

private:
	UPROPERTY()
	AAPlayerCharacter* Character;

	const int32 MaxSlots = 4;

	void SpawnDefaultWeapon();
};