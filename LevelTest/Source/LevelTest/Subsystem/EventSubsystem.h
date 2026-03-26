#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EventSubsystem.generated.h"

class AAHBaseItem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAmmoChanged, int32, CurrentAmmo, int32, SpareAmmo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, Health);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDisplay, FString, Content, bool, bIsvisible);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnSlotUpdated, int32, i, TSubclassOf<AAHBaseItem>, ItemClass, int32, Count);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquipFromSlot,int32, SlotIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEquipRequest, UAHItemData*, ItemData, int32, SlotIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathDelegate);

UCLASS()
class LEVELTEST_API UEventSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	static UEventSubsystem* Get(const UObject* WorldContext);
	
	FOnEquipFromSlot OnEquipFromSlot;
	FOnEquipRequest OnEquipRequest;
	FOnAmmoChanged OnAmmoChanged;
	FOnHealthChanged OnHealthChanged;
	FOnDisplay OnDisplay;
	FOnSlotUpdated OnSlotUpdated;
	FOnDeathDelegate OnDeath;
};
