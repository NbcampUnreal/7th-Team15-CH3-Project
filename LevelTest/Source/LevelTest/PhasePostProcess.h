#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhasePostProcess.generated.h"

class UPostProcessComponent;

UCLASS()
class LEVELTEST_API APhasePostProcess : public AActor
{
	GENERATED_BODY()
	
public:	
	APhasePostProcess();

	void UpdateHealthVignette(float HPPercent);

protected:
	virtual void BeginPlay() override;

	void UpdatePostProcess(int32 NewPhase);

	float CurrentPhaseVignette = 0.4f;

public:	
	UPROPERTY(VisibleAnywhere)
	UPostProcessComponent* PostProcessComp;

	float TargetVignette = 0.4f;
	float TargetGrain = 0.0f;

};

