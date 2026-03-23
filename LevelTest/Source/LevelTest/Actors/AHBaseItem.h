#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "Interface/AHInteractInterface.h"
#include "Characters/Player/AHPlayerCharacter.h"
#include "AHBaseItem.generated.h"

UCLASS()
class LEVELTEST_API AAHBaseItem : public AActor, public IAHInteractInterface
{
	GENERATED_BODY()
	
public:	
	AAHBaseItem();
	
	virtual void Interact(AActor* Interactor) override;
	
	virtual void OnEquipped();
	
	virtual void StartPrimeAction();
	virtual void EndPrimeAction();
	
	virtual void StartSecondaryAction();
	virtual void EndSecondaryAction();
	
	//variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Setting")
	FGameplayTag ItemTag; // 아이템 형식을 입력하기 위한 태그(무기, 회복, 키 등)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Setting")
	FString ItemName;
	
protected:
	virtual void BeginPlay() override;
	
	AAHPlayerCharacter* GetPlayerOwner() const;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Compnents")
	UStaticMeshComponent* MeshComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|Setting")
	int32 MaxStackSize = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|Setting")
	int32 CurrentStackSize = 1;

};
