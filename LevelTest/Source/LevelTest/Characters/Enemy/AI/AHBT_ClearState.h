#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AHBT_ClearState.generated.h"


class UBehaviorTreeComponent;

UCLASS()
class LEVELTEST_API UAHBT_ClearState : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UAHBT_ClearState();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector StateKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	uint8 TargetStateValue = 0;



	
};
