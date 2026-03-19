// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "World/AHBaseItem.h"
#include "AHBaseConsumableItem.generated.h"

/**
 * 
 */
UCLASS()
class LEVELTEST_API AAHBaseConsumableItem : public AAHBaseItem
{
	GENERATED_BODY()
	
public:
	AAHBaseConsumableItem();
	
	virtual void StartPrimeAction() override;
	virtual void StartSecondaryAction() override;
	virtual void EndSecondaryAction() override;
	
protected:
	virtual void BeginPlay() override;
	
	void ApplyHeal(AActor* Target);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Heal");
	float HealAmount;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Heal")
	float InteractRange = 300.f;
	
	bool bIsAiming = false;
};
