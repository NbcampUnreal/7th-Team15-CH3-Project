#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ClearState.generated.h"


class UBehaviorTreeComponent;

UCLASS()
class LEVELTEST_API UBTTask_ClearState : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_ClearState();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector StateKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	uint8 TargetStateValue = 0;



	
};
