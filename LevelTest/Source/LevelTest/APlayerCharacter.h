#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CombatInterface.h"
#include "GameplayTagContainer.h"
#include "GameplayTagAssetInterface.h"
#include "CombatComponent.h"
#include "InteractInterface.h"
#include "APlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UCharacterStatusComponent;
class UAHMainWidget;
class APhasePostProcess;

UCLASS()
class LEVELTEST_API AAPlayerCharacter : public ACharacter , public ICombatInterface, public IGameplayTagAssetInterface, public IInteractInterface
{
	GENERATED_BODY()

public:
	AAPlayerCharacter();

	void UpdateVisualState();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	APhasePostProcess* PostProcessHandler;

public:	

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


#pragma region Components 
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	UCameraComponent* CameraComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	UCharacterStatusComponent* StatusComp;

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

	void UpdateCrosshairVisibility(bool bIsWeaponEquipped);

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override { TagContainer = FactionTags; }


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Faction")
	FGameplayTagContainer FactionTags;


#pragma endregion


#pragma region combatAction
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UCombatComponent* CombatComp;

	void OnPrimeAction();
	void OnSecondAction(const FInputActionValue& Value);
	void OnSlot1();
	void OnSlot2();
	void OnSlot3();
	void OnSlot4();
	void OnRealod();
#pragma endregion

//Interact Action
protected:
	void ProcessInteract();

	virtual void Interact(AActor* Interactor) override {};

	UPROPERTY(BlueprintReadOnly)
	bool bIsAiming;

public:
	void ShowGameMessage(FString Message, bool bShow);

	void UpdateAmmoUI(int32 CurrentAmmo, int32 SpareAmmo);

	UAHMainWidget* GetMainWidget() const { return MainWidget; }
protected:
	UPROPERTY()
	UAHMainWidget* MainWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
	UAnimMontage* DamagedMontage;

};
