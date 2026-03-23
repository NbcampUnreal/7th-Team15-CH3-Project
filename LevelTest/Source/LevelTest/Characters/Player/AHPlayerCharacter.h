#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Characters/Components/AHCharacterStatusComponent.h"
#include "Characters/Components/AHCombatComponent.h"
#include "Interface/AHInteractInterface.h"
#include "EnhancedInput/Public/InputAction.h"
#include "AHPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UAHCharacterStatusComponent;

UCLASS()
class LEVELTEST_API AAHPlayerCharacter : public ACharacter,  public IAHInteractInterface, public IGenericTeamAgentInterface
{
    GENERATED_BODY()

public:
    AAHPlayerCharacter();

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual FGenericTeamId GetGenericTeamId() const override { return FGenericTeamId(0); } // 0번을 플레이어 세력으로
    // 번호만으로 피아, 적세력을 구분해서 불필요한 코드량을 줄이기 위함인가?
    
    void InputMove(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void OnInputJump(const FInputActionInstance& InputActionInstance);
    void SprintStart(const FInputActionValue& Value);
    void SprintEnd(const FInputActionValue& Value);
    void UpdateCrosshairVisibility(bool bIsWeaponEquipped);
    void ShowGameMessage(FString Message, bool bShow);
    void UpdateAmmoUI(int32 CurrentAmmo, int32 SpareAmmo);
    

   // UFUNCTION()
 //   void HandleDeath();

    // --- Variables ---
    UPROPERTY(VisibleAnywhere, Category = "Camera")
    USpringArmComponent* SpringArmComp;

    UPROPERTY(VisibleAnywhere, Category = "Camera")
    UCameraComponent* CameraComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
    UAHCharacterStatusComponent* StatusComp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float NormalSpeed = 400.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float SprintSpeedMultiply = 1.5f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
    float SprintSpeed;

protected:
    // --- Functions ---
    virtual void BeginPlay() override;
    virtual void Interact(AActor* Interactor) override {};
    virtual void PostInitializeComponents() override;

    void OnPrimeAction();
    void OnSecondAction(const FInputActionValue& Value);
    void OnSlot1();
    void OnSlot2();
    void OnSlot3();
    void OnSlot4();
    void OnReload();
    void ProcessInteract();

    // --- Variables ---
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    UAHCombatComponent* CombatComp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
    float InteractRange = 400.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
    UAnimMontage* DamagedMontage;

    UPROPERTY(BlueprintReadOnly)
    bool bIsAiming;
    
    float OriginalWalkSpeed;
private:
};