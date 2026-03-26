#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AHItemData.generated.h"

UCLASS()
class LEVELTEST_API UAHItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category= "Info")
	FText ItemName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|Info")
	FText ItemDescription;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Item|Sys")
	class UTexture2D* ItemIcon;
	
	
	UPROPERTY(EditAnywhere, Category= "Visual")
	TSubclassOf<class AAHBaseItem> ItemClass;
	
	UPROPERTY(EditAnywhere, Category= "ItemTag")
	FGameplayTag ItemTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Item|bConsume")
	bool bConsumable = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Item|Stack")
	int32 StackCount = 1;
	
};
