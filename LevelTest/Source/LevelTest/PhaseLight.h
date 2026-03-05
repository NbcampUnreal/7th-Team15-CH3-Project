#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhaseLight.generated.h"

UCLASS()
class LEVELTEST_API APhaseLight : public AActor
{
	GENERATED_BODY()
	
public:	
	APhaseLight();

protected:
	virtual void BeginPlay() override;

	void OnPhaseChanged(int32 NewPhase);

	void ToggleFlicker();

private:
	UPROPERTY(VisibleAnywhere)
	class UPointLightComponent* PointLight;

	FTimerHandle FlickerTimerHandle;
	float DefaultIntensity;

	UPROPERTY(EditAnywhere, Category = "Interval")
	float FlickerInterval = 0.1f;

};
