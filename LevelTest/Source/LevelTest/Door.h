#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "GameplayTagContainer.h"
#include "Door.generated.h"

UCLASS()
class LEVELTEST_API ADoor : public AActor, public IInteractInterface
{
	GENERATED_BODY()

public:
	ADoor();

	// 인터페이스 상속
	virtual void Interact(AActor* Interactor) override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere, Category = "Door Settings")
	FGameplayTag RequiredKeyTag;
	// 이 문을 열기 위해 필요한 열쇠 태그 (예: Tag.Key.Hospital_Main)

	bool bIsOpened = false;
	//문상태

	UPROPERTY(EditAnywhere, Category = "Door Settings")
	class USoundBase* OpenSound;

	UPROPERTY(EditAnywhere, Category = "Door Settings")
	class USoundBase* LockedSound;
};
