#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AHPhaseLight.generated.h"

UCLASS()
class LEVELTEST_API AAHPhaseLight : public AActor
{
	GENERATED_BODY()
	
public:	
	AAHPhaseLight();

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
