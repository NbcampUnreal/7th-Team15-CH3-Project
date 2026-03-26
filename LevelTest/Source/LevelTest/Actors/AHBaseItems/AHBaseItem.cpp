#include "AHBaseItem.h"
#include "Characters/Player/AHPlayerCharacter.h"
#include "Characters/Components/AHInventoryComponent.h"

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
	
	UAHInventoryComponent* InventoryComp = Interactor->FindComponentByClass<UAHInventoryComponent>();
	if (InventoryComp)
	{
		if (InventoryComp->AddItemToSlot(this->ItemData,CurrentStackSize))
		{
			Destroy();
		}
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