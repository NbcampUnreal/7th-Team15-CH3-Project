#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "GameplayTagContainer.h"
#include "GameplayTagAssetInterface.h"
#include "Component/AHCharacterStatusComponent.h"
#include "Component/AHCombatComponent.h"
#include "Interface/AHInteractInterface.h"
#include "AHPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UAHCharacterStatusComponent;
class UAHMainWidget;
class AAHPhasePostProcess;

UCLASS()
class LEVELTEST_API AAHPlayerCharacter : public ACharacter, public IGameplayTagAssetInterface, public IAHInteractInterface
{
    GENERATED_BODY()

public:
    AAHPlayerCharacter();

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override { TagContainer = FactionTags; }

    void UpdateVisualState();
    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void StartJump(const FInputActionValue& Value);
    void StopJump(const FInputActionValue& Value);
    void SprintStart(const FInputActionValue& Value);
    void SprintEnd(const FInputActionValue& Value);
    void UpdateCrosshairVisibility(bool bIsWeaponEquipped);
    void ShowGameMessage(FString Message, bool bShow);
    void UpdateAmmoUI(int32 CurrentAmmo, int32 SpareAmmo);
    
    UAHMainWidget* GetMainWidget() const { return MainWidget; }

    UFUNCTION()
    void HandleDeath();

    // --- Variables ---
    UPROPERTY(VisibleAnywhere, Category = "Camera")
    USpringArmComponent* SpringArmComp;

    UPROPERTY(VisibleAnywhere, Category = "Camera")
    UCameraComponent* CameraComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
    UAHCharacterStatusComponent* StatusComp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float NormalSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float SprintSpeedMultiple;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
    float SprintSpeed;

protected:
    // --- Functions ---
    virtual void BeginPlay() override;
    virtual void Interact(AActor* Interactor) override {};

    void OnPrimeAction();
    void OnSecondAction(const FInputActionValue& Value);
    void OnSlot1();
    void OnSlot2();
    void OnSlot3();
    void OnSlot4();
    void OnReload();
    void ProcessInteract();

    // --- Variables ---
    UPROPERTY()
    AAHPhasePostProcess* PostProcessHandler;

    UPROPERTY()
    UAHMainWidget* MainWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    UAHCombatComponent* CombatComp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
    float InteractRange = 400.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Faction")
    FGameplayTagContainer FactionTags;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
    UAnimMontage* DamagedMontage;

    UPROPERTY(BlueprintReadOnly)
    bool bIsAiming;

private:
};