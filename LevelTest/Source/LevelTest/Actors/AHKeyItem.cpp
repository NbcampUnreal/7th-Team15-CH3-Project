#include "AHKeyItem.h"
#include "Characters/Player/AHPlayerCharacter.h"
#include "Characters/Components/AHCombatComponent.h"
#include "Components/StaticMeshComponent.h"

AAHKeyItem::AAHKeyItem()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	MeshComp->SetCollisionResponseToAllChannels(ECR_Block);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AAHKeyItem::Interact(AActor* Interactor)
{
	AAHPlayerCharacter* Player = Cast<AAHPlayerCharacter>(Interactor);
	if (!Player) return;

	UAHCombatComponent* CombatComp = Player->FindComponentByClass<UAHCombatComponent>();
	if (CombatComp)
	{
		CombatComp->AddKey(KeyTag);

		Player->ShowGameMessage(PickupMessage, true);

		Destroy();
	}
}