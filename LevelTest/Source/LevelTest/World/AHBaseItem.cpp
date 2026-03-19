#include "AHBaseItem.h"
#include "Character/AHPlayerCharacter.h"
#include "Component/AHCombatComponent.h"

AAHBaseItem::AAHBaseItem()
{
	PrimaryActorTick.bCanEverTick = false;
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
	
	MeshComp->SetCollisionResponseToAllChannels(ECR_Block);
	// 
	MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	// 충돌 활성화 상태, query : 레이캐스트, 스윕, 오버랩 수행가능, physics : 언리얼 엔진 물리엔진 상호작용허가
}


void AAHBaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAHBaseItem::Interact(AActor* Interactor)
{
	if (!Interactor) return;
	
	UAHCombatComponent* CombatComp = Interactor->FindComponentByClass<UAHCombatComponent>();
	if (CombatComp)
	{
		CombatComp->AddWeaponToQuickbar(this ->GetClass());
		Destroy();
	}
}

void AAHBaseItem::StartPrimeAction()
{
}

void AAHBaseItem::EndPrimeAction()
{

}

void AAHBaseItem::StartSecondaryAction()
{

}

void AAHBaseItem::EndSecondaryAction()
{

}

void AAHBaseItem::OnEquipped()
{

}

AAHPlayerCharacter* AAHBaseItem::GetPlayerOwner() const
{
	return Cast<AAHPlayerCharacter>(GetOwner());
}