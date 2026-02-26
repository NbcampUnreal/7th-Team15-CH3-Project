#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseNoiseObject.generated.h"

class UStaticMeshComponent;
class USoundBase;

UCLASS()
class LEVELTEST_API ABaseNoiseObject : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseNoiseObject();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="Components")
	UStaticMeshComponent* MeshComp;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category ="AI")
	float NoiseLoudness = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float NoiseRange = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Sound")
	USoundBase* CollisionSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Sound")
	float PitchMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float NoiseCooldown = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float ImpulsetoMakeSound = 3000.f;

	float LastNoiseTime = 0.f;
};
