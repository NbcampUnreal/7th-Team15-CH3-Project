#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AI/AHAIState.h"
#include "GameplayTagContainer.h"
#include "GameplayTagAssetInterface.h"
#include "AHEnemy.generated.h"

class UAHCharacterStatusComponent;
class UAnimMontage;

UENUM(BlueprintType)
enum class EEnemyDisposition : uint8
{
    Neutral UMETA(DisplayName = "Neutral"),
    Hostile UMETA(DisplayName = "Hostile"),
    Friendly UMETA(DisplayName = "Friendly")
};

UCLASS()
class LEVELTEST_API AAHEnemy : public ACharacter, public IGameplayTagAssetInterface
{
    GENERATED_BODY()

public:
    // --- Public Functions ---
    AAHEnemy();

    virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContaniner) const override { TagContaniner = FactionTags; }

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void CheckHit();

    UFUNCTION()
    void HandleDeath();

    void BecomeHostile();
    void BecomeNeutral();
    void PlayAttack();
    void PlayInvestigate();
    void PlayRageWake();
    void Revive();

    EEnemyDisposition GetDisposition() const { return CurrentDisposition; }

    // --- Public Variables (Components & Test) ---
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
    UAHCharacterStatusComponent* StatusComp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
    EEnemyState TestCase;

protected:
    // --- Protected Functions ---
    virtual void BeginPlay() override;

    // --- Protected Variables (Settings & Montages) ---
    // 블루프린트에서 수정 가능한 설정값 및 에셋들입니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float AttackDamage = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float AngerDuration = 10.f; 

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Revive")
    float ReviveTime = 30.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    EEnemyState CurrentState;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    EEnemyDisposition CurrentDisposition = EEnemyDisposition::Neutral;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Faction")
    FGameplayTagContainer FactionTags;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
    UAnimMontage* AttackMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
    UAnimMontage* InvestigateMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
    UAnimMontage* DeadMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
    UAnimMontage* WakeMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
    UAnimMontage* RageWakeMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
    UAnimMontage* GrabMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
    UAnimMontage* DamagedMontage;

private:
    // --- Private Variables (Internal Handlers) ---
    // 내부 로직용 타이머 핸들입니다.
    FTimerHandle AngerTimerHandle;
    FTimerHandle ReviveTimerHandle;
};