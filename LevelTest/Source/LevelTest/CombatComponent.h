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

	void Reload();

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

	UFUNCTION(BlueprintCallable, Category = "Inventory|Quest")
	void AddKey(FGameplayTag KeyTag);

	UFUNCTION(BlueprintPure, Category = "Inventory|Quest")
	bool HasKey(FGameplayTag KeyTag) const;

	void RemoveKey(FGameplayTag KeyTag);

private:
	UPROPERTY()
	AAPlayerCharacter* Character;

	const int32 MaxSlots = 4;

	int32 CurrentSlotIndex = -1;

	void SpawnDefaultWeapon();

	UPROPERTY()
	TArray<int32> SlotAmmoCounts;

	UPROPERTY(EditAnywhere, Category = "Combat|Ammo")
	int32 SpareAmmo = 60;

	bool bIsReloading = false;

	void FinishReloading();

	FTimerHandle ReloadTimerHandle;

	UPROPERTY(VisibleAnywhere, Category = "Inventory|Quest")
	TArray<FGameplayTag> OwnedKeys;

};