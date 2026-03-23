#include "AHBT_FindRandomLocation.h"
#include"AIController.h"
#include"NavigationSystem.h"
#include"BehaviorTree/BlackBoardComponent.h"

UAHBT_FindRandomLocation::UAHBT_FindRandomLocation()
{
	NodeName = TEXT("Find Random Location");

	PatrolLocationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UAHBT_FindRandomLocation, PatrolLocationKey));
}

EBTNodeResult::Type UAHBT_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AiController = OwnerComp.GetAIOwner();
	if (AiController == nullptr || AiController->GetPawn() == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavSystem == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	const FVector Origin = AiController->GetPawn()->GetActorLocation();
	FNavLocation RandomLocation;

	const bool bFound = NavSystem->GetRandomReachablePointInRadius(Origin, SearchRadius, RandomLocation);
	if (bFound)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(PatrolLocationKey.SelectedKeyName, RandomLocation.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;

}
