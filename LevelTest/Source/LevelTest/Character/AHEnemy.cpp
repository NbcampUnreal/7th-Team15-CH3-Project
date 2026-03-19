#include "AHEnemy.h"
#include"Component/AHCharacterStatusComponent.h"
#include"AI/AHAIState.h"

AAHEnemy::AAHEnemy()
{
 	PrimaryActorTick.bCanEverTick = false;

	StatusComp = CreateDefaultSubobject<UAHCharacterStatusComponent>(TEXT("StatusComp"));

	CurrentState = EEnemyState::Idle;


}

void AAHEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	if (!StatusComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("AAHEnemy NO StatusCOmp Now"));
		StatusComp = FindComponentByClass<UAHCharacterStatusComponent>();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AAHEnemy StatusCOmp Now"));
	}


	if (StatusComp)
	{
		StatusComp->OnDeath.AddDynamic(this, &AAHEnemy::HandleDeath);
	}


}

void AAHEnemy::CheckHit()
{
	FHitResult HitResult;
	FVector Start = GetActorLocation() + GetActorForwardVector() * 50.f;
	FVector End = Start + GetActorForwardVector() * 100.f;

	FCollisionQueryParams Params;

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);

	Params.AddIgnoredActors(IgnoreActors);
	bool bHit = GetWorld()->SweepSingleByChannel(
		HitResult, Start, End, FQuat::Identity,
		ECC_Pawn, FCollisionShape::MakeSphere(40.f), Params
	);

	if (bHit)
	{
		
	}
}




void AAHEnemy::HandleDeath()
{
	CurrentState = EEnemyState::Downed;

	if (DeadMontage) { PlayAnimMontage(DeadMontage); }

	GetWorldTimerManager().SetTimer(ReviveTimerHandle, this, &AAHEnemy::Revive, ReviveTime, false);
}

void AAHEnemy::BecomeHostile()
{
	CurrentDisposition = EEnemyDisposition::Hostile;
	if (AngerDuration >= 30.f)
	{
		CurrentState = EEnemyState::Rage;
		PlayRageWake();
	}

	GetWorldTimerManager().SetTimer(AngerTimerHandle, this, &AAHEnemy::BecomeNeutral, AngerDuration, false);
	AngerDuration += 10.f;

	UE_LOG(LogTemp, Warning, TEXT("Monster Anger Test Now Hostile"));
}

void AAHEnemy::BecomeNeutral()
{
	CurrentDisposition = EEnemyDisposition::Neutral;

	UE_LOG(LogTemp, Warning, TEXT("Monster Anger Test Now Neutral"));
}

void AAHEnemy::PlayAttack()
{
	if (CurrentState == EEnemyState::Rage)
	{
		if (GrabMontage)
		{
			PlayAnimMontage(GrabMontage);
		}
	}
	else 
	{
		if (AttackMontage)
		{
		PlayAnimMontage(AttackMontage);
		}
	}
}

void AAHEnemy::PlayInvestigate()
{
	if (InvestigateMontage)
	{
		PlayAnimMontage(InvestigateMontage);
	}
}

void AAHEnemy::PlayRageWake()
{
	if (RageWakeMontage) { PlayAnimMontage(RageWakeMontage); }
}

void AAHEnemy::Revive()
{
	if (StatusComp) { StatusComp->ResetHealth(); }

	if (WakeMontage) { PlayAnimMontage(WakeMontage); } // 일어나는 애니메이션 재생,

	if (FMath::RandBool())
	{
		CurrentState = EEnemyState::Idle; //부활후 idle 상태로 부활
	}
	else // 50퍼센트 확률로 적대적 상태로 부활
	{
		BecomeHostile(); // 적대상태 on
	}
}
