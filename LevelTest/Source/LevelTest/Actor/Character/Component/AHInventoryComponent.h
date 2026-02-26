#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AHInventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEVELTEST_API UAHInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAHInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Inventory")
	AActor* CurrentEquippedItem;

	void EquipItem(AActor* NewItem);

	void UseEquippedItem();

	void ReloadItem();

	FORCEINLINE AActor* GetCurrentItem() const { return CurrentEquippedItem; }
		
};
