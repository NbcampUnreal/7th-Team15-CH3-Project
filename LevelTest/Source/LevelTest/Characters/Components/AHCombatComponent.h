#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "AHCombatComponent.generated.h"

class AAHBaseWeapon;
class AAHPlayerCharacter; 

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LEVELTEST_API UAHCombatComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UAHCombatComponent();

    void Reload();
    void AddWeaponToQuickbar(TSubclassOf<AAHBaseWeapon> WeaponClass);
    void SwitchWeapon(int32 SlotIndex);
    void ProcessPrimaryAction();
    void ProcessSecondaryAction(bool bIsPressed);
    void EquipWeapon(AAHBaseWeapon* WeaponToEquip);

    UFUNCTION(BlueprintCallable, Category = "Inventory|Quest")
    void AddKey(FGameplayTag KeyTag);

    UFUNCTION(BlueprintPure, Category = "Inventory|Quest")
    bool HasKey(FGameplayTag KeyTag) const;

    UFUNCTION(BlueprintCallable, Category = "Inventory|Quest")
    void RemoveKey(FGameplayTag KeyTag);
    
    UPROPERTY(VisibleAnywhere, Category = "Inventory")
    TArray<TSubclassOf<class AAHBaseWeapon>> QuickbarSlots;

    UPROPERTY(EditAnywhere, Category = "Combat")
    TSubclassOf<AAHBaseWeapon> DefaultWeaponClass;

    UPROPERTY(BlueprintReadWrite, Category = "Combat")
    AAHBaseWeapon* EquippedWeapon;

protected:
    // --- Protected Functions ---
    virtual void BeginPlay() override;

private:
    void SpawnDefaultWeapon();
    void FinishReloading();
    
    UPROPERTY()
    AAHPlayerCharacter* Character;
    
    UPROPERTY()
    TArray<int32> SlotAmmoCounts;

    UPROPERTY(EditAnywhere, Category = "Combat|Ammo")
    int32 SpareAmmo = 60;

    UPROPERTY(VisibleAnywhere, Category = "Inventory|Quest")
    TArray<FGameplayTag> OwnedKeys;

    FTimerHandle ReloadTimerHandle;

    const int32 MaxSlots = 4;

    int32 CurrentSlotIndex = -1;

    bool bIsReloading = false;
};