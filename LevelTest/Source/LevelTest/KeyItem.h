#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h" 
#include "GameplayTagContainer.h"
#include "KeyItem.generated.h"

UCLASS()
class LEVELTEST_API AKeyItem : public AActor, public IInteractInterface
{
	GENERATED_BODY()

public:
	AKeyItem();

	virtual void Interact(AActor* Interactor) override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, Category = "Key Settings")
	FGameplayTag KeyTag;

	UPROPERTY(EditAnywhere, Category = "Key Settings")
	FString PickupMessage = TEXT("열쇠를 획득했습니다.");

};
