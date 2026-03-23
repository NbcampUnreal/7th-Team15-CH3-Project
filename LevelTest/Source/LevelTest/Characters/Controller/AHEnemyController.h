#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "AHEnemyController.generated.h"


UCLASS()
class LEVELTEST_API AAHEnemyController : public AAIController
{
	GENERATED_BODY()
	AAHEnemyController();

public:
	virtual void OnPossess(APawn* InPawn) override;


protected:
	UFUNCTION()
	void OnTargetPerceptionUploaded(AActor* Actor, FAIStimulus Stimulus);

private:
	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<class UBehaviorTree> BTAsset;



};
