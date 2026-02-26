#include "BTTask_ClearState.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_ClearState::UBTTask_ClearState()
{
	NodeName = TEXT("Clear Enemy State"); // 비헤이비어 트리에 보일 이름
}

EBTNodeResult::Type UBTTask_ClearState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();

	if (BB)
	{
		//선택한 키(에너미 스테잍!!) 에 원하는 값을 넣는다(ai 스테이트에 정리해둔 순서로 idle = 0, patrol = 1, investigate = 2, chase = 3 attack = 4)
		BB->SetValueAsEnum(StateKey.SelectedKeyName, TargetStateValue);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}