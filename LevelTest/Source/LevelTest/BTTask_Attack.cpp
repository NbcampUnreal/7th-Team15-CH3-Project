#include "BTTask_Attack.h"

#include"AIController.h"
#include"GameFramework/Character.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true; // 이게 없으면 TickTask가 아예 실행되지 않다고 하는데...?
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Owner = OwnerComp.GetAIOwner();
	if (Owner == nullptr)
	{
		return EBTNodeResult::Aborted;
	}

	ACharacter* AiController = Cast<ACharacter>(Owner->GetPawn());

	if (AiController == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AiController->PlayAnimMontage(AttackMontage);
	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* Owner = OwnerComp.GetAIOwner();
	if (Owner == nullptr)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	ACharacter* AICharacter = Cast<ACharacter>(Owner->GetPawn());
	if (AICharacter == nullptr)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	UAnimInstance* AnimInstance = AICharacter->GetMesh()->GetAnimInstance();
	if (AnimInstance == nullptr)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	bool bStopped = AnimInstance->Montage_GetIsStopped(AttackMontage);
	if (bStopped)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}


}
