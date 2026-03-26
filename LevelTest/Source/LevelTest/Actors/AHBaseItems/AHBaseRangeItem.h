#pragma once

#include "CoreMinimal.h"
#include "Actors/AHBaseItems/AHBaseItem.h"
#include "AHBaseRangeItem.generated.h"

class USoundBase;

UCLASS()
class LEVELTEST_API AAHBaseRangeItem : public AAHBaseItem
{
	GENERATED_BODY()

public:
	virtual void StartPrimeAction() override;
	
	UPROPERTY(EditAnywhere, Category = "Weapon|Slot")
	int32 CurrentAmmo = 15;
	
protected:
	void Fire();
	
	void PlayEmptySound();
	
	UPROPERTY(EditAnywhere, Category = "Weapon|Sound")
	USoundBase* EmptySound;
	
	UPROPERTY(EditAnywhere, Category = "Weapon|Stat")
	float TraceRange = 500.f;
	
	UPROPERTY(EditAnywhere, Category = "Weapon|Stat")
	float Damage = 20.f;
	
	//UPROPERTY(EditAnywhere, Category = "Weapon|Effect")
	
};
