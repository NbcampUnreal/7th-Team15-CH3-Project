#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AHCombatComponent.generated.h"

class ABaseWeapon;
class AAHPlayerCharacter;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LEVELTEST_API UAHCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAHCombatComponent();

protected:
	virtual void BeginPlay() override;

public:
	void AddWeaponToQuickbar(TSubclassOf<ABaseWeapon> WeaponClass);
	void SwitchWeapon(int32 SlotIndex);
	void ProcessPrimaryAction();
	void ProcessSecondaryAction(bool bIsPressed);
	void EquipWeapon(ABaseWeapon* WeaponToEquip);

protected:
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<TSubclassOf<class ABaseWeapon>> QuickbarSlots;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<ABaseWeapon> DefaultWeaponClass;

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	ABaseWeapon* EquippedWeapon;

private:
	UPROPERTY()
	AAHPlayerCharacter* Character;

	const int32 MaxSlots = 4;

	void SpawnDefaultWeapon();
};
