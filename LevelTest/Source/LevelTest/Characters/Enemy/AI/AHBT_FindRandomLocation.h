#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AHBT_FindRandomLocation.generated.h"

UCLASS()
class LEVELTEST_API UAHBT_FindRandomLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UAHBT_FindRandomLocation();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UPROPERTY(EditAnywhere, Category = "BlackBoard")
	FBlackboardKeySelector PatrolLocationKey;
	
	UPROPERTY(EditAnywhere, Category ="AI")
	float SearchRadius = 1000.f;

};
