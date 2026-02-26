#include "AHEnemyController.h"
#include "BehaviorTree/BehaviorTree.h"
#include"BehaviorTree/BlackboardComponent.h"
#include"Perception/AIPerceptionComponent.h"
#include"Perception/AISense_sight.h"
#include"Perception/AISense_Hearing.h"
#include"GameplayTagAssetInterface.h"
#include"AHEnemy.h"
#include"AIState.h"

AAHEnemyController::AAHEnemyController()
{
}

void AAHEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BTAsset)
	{
		RunBehaviorTree(BTAsset);
	}

	UAIPerceptionComponent* PerComp = FindComponentByClass<UAIPerceptionComponent>();

	if (!PerComp && InPawn)
	{
		PerComp = InPawn->FindComponentByClass<UAIPerceptionComponent>();
	}

	if (PerComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("성공] 퍼셉션 컴포넌트"));
		PerComp->OnTargetPerceptionUpdated.AddDynamic(this, &AAHEnemyController::OnTargetPerceptionUploaded);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("에러 퍼셉션 컴포넌트"));
	}
}

void AAHEnemyController::OnTargetPerceptionUploaded(AActor* Actor, FAIStimulus Stimulus)
{
	UE_LOG(LogTemp, Warning, TEXT("Perception Update Detected! Target: %s"), *Actor->GetName());
	UBlackboardComponent* BB = GetBlackboardComponent();
	if (!BB || !Actor) return;

	if (Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
	{
		IGameplayTagAssetInterface* TagInterface = Cast<IGameplayTagAssetInterface>(Actor);
		
		if (!TagInterface)
		{
			UE_LOG(LogTemp, Warning, TEXT("Couldn't recognize"));
			return;
		}
		FGameplayTagContainer TargetTags;
		TagInterface->GetOwnedGameplayTags(TargetTags);

		if (Stimulus.WasSuccessfullySensed())
		{
			AAHEnemy* MyEnemy = Cast<AAHEnemy>(GetPawn());

			if (MyEnemy && MyEnemy->GetDisposition() == EEnemyDisposition::Hostile)
			{
				BB->SetValueAsObject(BBKeys::TargetActor, Actor);

				BB->SetValueAsEnum(BBKeys::EnemyState, (uint8)EEnemyState::Chase);
			}
		}
		else
		{
			AAHEnemy* MyEnemy = Cast<AAHEnemy>(GetPawn());
			bool bIsAttacking = false;
			if (MyEnemy && MyEnemy->GetMesh())
			{
				UAnimInstance* AnimInst = MyEnemy->GetMesh()->GetAnimInstance();
				if (AnimInst && AnimInst->IsAnyMontagePlaying())
				{
					bIsAttacking = true;
				}
			}
			if (!bIsAttacking)
			{
				BB->ClearValue(BBKeys::TargetActor);
				BB->SetValueAsEnum(BBKeys::EnemyState, (uint8)EEnemyState::Idle);
				UE_LOG(LogTemp, Warning, TEXT("Target Lost Test"));
			}
		}
	}
	else if (Stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>())
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			BB->SetValueAsVector(BBKeys::TargetLocation, Stimulus.StimulusLocation);
			BB->SetValueAsEnum(BBKeys::EnemyState, (uint8)EEnemyState::Investigate);
		}
	}
}

