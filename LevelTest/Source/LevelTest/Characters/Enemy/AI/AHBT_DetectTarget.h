#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "AHBT_DetectTarget.generated.h"

UCLASS()
class LEVELTEST_API UAHBT_DetectTarget : public UBTService
{
	GENERATED_BODY()
	
public:
	UAHBT_DetectTarget();

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category ="BlackBoard")
	FBlackboardKeySelector TargetActorKey;

	UPROPERTY(EditAnywhere, Category ="AI")
	float DetectRadius = 1000.0f;
};
