#include "AHDoor.h"
#include "Characters/Player/AHPlayerCharacter.h"
#include "Characters/Components/AHCombatComponent.h"
#include "Kismet/GameplayStatics.h"

AHDoor::AHDoor()
{
	PrimaryActorTick.bCanEverTick = false;
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = DoorMesh;
}

void AHDoor::Interact(AActor* Interactor)
{
	if (bIsOpened)
	{
		return; // 이미 열렸다면 무시
	}

	AAHPlayerCharacter* Player = Cast<AAHPlayerCharacter>(Interactor);
	if (!Player)
	{
		return;
	}

	UAHCombatComponent* CombatComp = Player->FindComponentByClass<UAHCombatComponent>();
	if (CombatComp)
	{
		// 1. 열쇠 소지 여부 확인
		if (CombatComp->HasKey(RequiredKeyTag))
		{
			// 2. 문 열림 처리 (시간 관계상 90도 회전으로 대체)
			SetActorRotation(GetActorRotation() + FRotator(0.f, 90.f, 0.f));

			if (OpenSound) UGameplayStatics::PlaySoundAtLocation(this, OpenSound, GetActorLocation());

			Player->ShowGameMessage(TEXT("문이 열렸습니다."), true);
			bIsOpened = true;

			// 필요하다면 열쇠 소모 (일회용일 경우)
			// CombatComp->RemoveKey(RequiredKeyTag); 
		}
		else
		{
			// 3. 열쇠가 없을 때 피드백
			if (LockedSound) UGameplayStatics::PlaySoundAtLocation(this, LockedSound, GetActorLocation());
			Player->ShowGameMessage(TEXT("잠겨 있습니다. 열쇠가 필요합니다."), true);
		}
	}
}