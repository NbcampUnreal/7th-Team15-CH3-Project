#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "InteractInterface.h"
#include "BaseWeapon.generated.h"

class USkeletalMeshComponent;
class UParticleSystem;
class USoundBase;

UCLASS()
class LEVELTEST_API ABaseWeapon : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	ABaseWeapon();

	virtual void Fire(const FVector& ShootLocation, const FRotator& ShootingRotation);

	virtual void SecondaryAction(bool bIsPressed);

	virtual void Interact(AActor* Interactor) override;
protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
	float FireRange = 5000.f;
	// 총 사거리

	UPROPERTY(EditAnywhere, Category = "Weapon Stats")
	float BaseDamage = 20.f;
	// 기본 데미지

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* FireSound;
	// 사격 시 재생할 소리
	
	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* MuzzleFlash;
	// 사격 이펙트 나아아중에

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* ImpactEffect;
	// 탄착 이펙트 나아아중에

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* EmptySound; // 탄약이 없을 때 재생할 소리

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* ReloadSound; // 탄약이 없을 때 재생할 소리
	
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool bDrawDebugLine = true;
	// 디버그용 라인 표시 여부

	UPROPERTY(EditAnywhere, Category = "Weapon Stats")
	bool bIsAiming = false;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
	FGameplayTag WeaponTag;

	FORCEINLINE class UStaticMeshComponent* GetStaticMeshComp() const { return StaticMeshComp; }
	FORCEINLINE class USkeletalMeshComponent* GetWeaponMesh() const { return WeaponMesh; }

	UPROPERTY(EditAnywhere, Category = "Effects")
	UAnimMontage* FireMontage;

	UPROPERTY(EditAnywhere, Category = "Ammo")
	int32 MaxAmmo = 15; // 탄창 최대 용량

	UPROPERTY(VisibleAnywhere, Category = "Ammo")
	int32 CurrentAmmo; // 현재 탄창에 남은 총알

public:
	void PlayEmptySound();

};
