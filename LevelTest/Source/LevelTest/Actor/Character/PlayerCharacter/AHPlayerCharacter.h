#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "GameplayTagContainer.h"
#include "GameplayTagAssetInterface.h"
#include "Actor/Character/Interface/AHCombatInterface.h"
#include "Actor/Character/Interface/AHInteractInterface.h"
#include "AHPlayerCharacter.generated.h"

class UAHCombatComponent;
class USpringArmComponent;
class UCameraComponent;
class UAHCharacterStatusComponent;

UCLASS()
class LEVELTEST_API AAHPlayerCharacter : public ACharacter , public IAHCombatInterface, public IGameplayTagAssetInterface, public IAHInteractInterface
{
	GENERATED_BODY()

public:
	AAHPlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:	

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


#pragma region Components 
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	UCameraComponent* CameraComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	UAHCharacterStatusComponent* StatusComp;

#pragma endregion

#pragma region Input Actions(EnhancedOnly)
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartJump(const FInputActionValue& Value);
	void StopJump(const FInputActionValue& Value);
	void SprintStart(const FInputActionValue& Value);
	void SprintEnd(const FInputActionValue& Value);

#pragma endregion

#pragma region Movement Speed

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float NormalSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintSpeedMultiple;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float SprintSpeed;

#pragma endregion

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	float InteratRange = 400.f;

#pragma region CombatInterface
public:
	virtual void GetDamage(float DamageAmount) override;
#pragma endregion


public:
	UFUNCTION()
	void HandleDeath();

#pragma region TagInterface

public:

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override { TagContainer = FactionTags; }


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Faction")
	FGameplayTagContainer FactionTags;


#pragma endregion


#pragma region combatAction
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UAHCombatComponent* CombatComp;

	void OnPrimeAction();
	void OnSecondAction(const FInputActionValue& Value);
	void OnSlot1();
	void OnSlot2();
	void OnSlot3();
	void OnSlot4();
#pragma endregion

//Interact Action
protected:
	void ProcessInteract();

	virtual void Interact(AActor* Interactor) override {};

	UPROPERTY(BlueprintReadOnly)
	bool bIsAiming;
};
