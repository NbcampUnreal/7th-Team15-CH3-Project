#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/AHInteractInterface.h" 
#include "GameplayTagContainer.h"
#include "AHKeyItem.generated.h"

UCLASS()
class LEVELTEST_API AAHKeyItem : public AActor, public IAHInteractInterface
{
	GENERATED_BODY()

public:
	AAHKeyItem();

	virtual void Interact(AActor* Interactor) override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, Category = "Key Settings")
	FGameplayTag KeyTag;

	UPROPERTY(EditAnywhere, Category = "Key Settings")
	FString PickupMessage = TEXT("열쇠를 획득했습니다.");

};
