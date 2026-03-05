#include "KeyItem.h"
#include "APlayerCharacter.h"
#include "CombatComponent.h"
#include "Components/StaticMeshComponent.h"

AKeyItem::AKeyItem()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	MeshComp->SetCollisionResponseToAllChannels(ECR_Block);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AKeyItem::Interact(AActor* Interactor)
{
	AAPlayerCharacter* Player = Cast<AAPlayerCharacter>(Interactor);
	if (!Player) return;

	UCombatComponent* CombatComp = Player->FindComponentByClass<UCombatComponent>();
	if (CombatComp)
	{
		CombatComp->AddKey(KeyTag);

		Player->ShowGameMessage(PickupMessage, true);

		Destroy();
	}
}