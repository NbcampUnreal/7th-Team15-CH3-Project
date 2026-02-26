#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include"CombatInterface.h"
#include"AIState.h"
#include "GameplayTagContainer.h"
#include "GameplayTagAssetInterface.h"
#include "AHEnemy.generated.h"

class UCharacterStatusComponent;
class UAnimMontage;

UENUM(BlueprintType)
enum class EEnemyDisposition : uint8
{
	Neutral UMETA(DisplayName = "Neutral"),
	Hostile UMETA(DisplayName = "Hostile"),
	Friendly UMETA(DisplayName = "Friendly")
};


UCLASS()
class LEVELTEST_API AAHEnemy : public ACharacter, public ICombatInterface, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	AAHEnemy();


protected:
	virtual void BeginPlay() override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	UCharacterStatusComponent* StatusComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float AttackDamage = 10.f;

	
public:

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void CheckHit();

	virtual void GetDamage(float DamageAmount) override;

	UFUNCTION()
	void HandleDeath();


#pragma region AIControl
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	EEnemyState CurrentState;


#pragma endregion

public:
	UPROPERTY(EditAnywhere, BLueprintReadWrite, Category = "Test")
	EEnemyState TestCase;

#pragma region TagInterface

public: 
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContaniner) const override { TagContaniner = FactionTags; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Faction")
	FGameplayTagContainer FactionTags;

#pragma endregion

#pragma region Disposition

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	EEnemyDisposition CurrentDisposition = EEnemyDisposition::Neutral;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float AngerDuraction = 10.f; // 분노 지속시간(아직 자세한 수치는 미정)

	FTimerHandle AngerTimerHandle;

public:

	void BecomeHostile();
	void BecomeNeutral();

	EEnemyDisposition GetDisposition() const { return CurrentDisposition; }


#pragma endregion

#pragma region AnimMontage

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
	UAnimMontage* AttackMontage; //공격 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
	UAnimMontage* InvestigateMontage; // 조사, 배회

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
	UAnimMontage* DeadMontage; // 일시적 무력화

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
	UAnimMontage* WakeMontage; // 무력화에서 일어남

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
	UAnimMontage* RageWakeMontage; // 레이지 상태로 돌입,

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
	UAnimMontage* GrabMontage; // 레이지 상태에서하는 특수공격 모션,

	void PlayAttack();

	void PlayInvestigate();

	void PlayRageWake();

#pragma endregion


#pragma region Revive

	FTimerHandle ReviveTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Revive")
	float ReviveTime = 30.f; // 부활대기시간

	void Revive();

#pragma endregion
};
