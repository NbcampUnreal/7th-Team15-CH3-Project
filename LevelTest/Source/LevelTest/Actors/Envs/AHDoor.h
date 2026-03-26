#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/AHInteractInterface.h"
#include "GameplayTagContainer.h"
#include "AHDoor.generated.h"

UCLASS()
class LEVELTEST_API AHDoor : public AActor, public IAHInteractInterface
{
	GENERATED_BODY()

public:
	AHDoor();

	// 인터페이스 상속 구현
	virtual void Interact(AActor* Interactor) override;

protected:
	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere, Category = "Door Settings")
	FGameplayTag RequiredKeyTag;

	UPROPERTY(EditAnywhere, Category = "Door Settings")
	class USoundBase* OpenSound;

	UPROPERTY(EditAnywhere, Category = "Door Settings")
	class USoundBase* LockedSound;

	bool bIsOpened = false;
	FRotator TargetRotation;

};