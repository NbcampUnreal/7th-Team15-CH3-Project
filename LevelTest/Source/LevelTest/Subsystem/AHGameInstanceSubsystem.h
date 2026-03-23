#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AHGameInstanceSubsystem.generated.h"

class AAHBaseItem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FonAmmoChanged, int32, CurrentAmmo, int32, SpareAmmo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FonHealthChanged, float, Health);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FonDisplay, FString, Content, bool, bIsvisible);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnSlotUpdated, int32, i, TSubclassOf<AAHBaseItem>, ItemClass, int32, Count);

UCLASS()
class LEVELTEST_API UAHGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	
public:
	FonAmmoChanged OnAmmoChanged;
	FonHealthChanged OnHealthChanged;
	FonDisplay OnDisplay;
	FOnSlotUpdated OnSlotUpdated;
};
