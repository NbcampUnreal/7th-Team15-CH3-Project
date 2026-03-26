#include "AHDoor.h"

#include "Characters/Components/AHInventoryComponent.h"
#include "Characters/Player/AHPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

AHDoor::AHDoor()
{
	PrimaryActorTick.bCanEverTick = true;
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
	
	UAHInventoryComponent* InventoryComp = Player->FindComponentByClass<UAHInventoryComponent>();
	if (InventoryComp)
	{
		if (InventoryComp->CheckItemByTag(RequiredKeyTag))
		{
			TargetRotation = GetActorRotation() + FRotator(0.f, 90.f, 0.f);
			bIsOpened = true;
			if (OpenSound) UGameplayStatics::PlaySoundAtLocation(this, OpenSound, GetActorLocation());
		}
		else
		{
			if (LockedSound) UGameplayStatics::PlaySoundAtLocation(this, LockedSound, GetActorLocation());
			
		}
	}
}

void AHDoor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (bIsOpened)
	{
		FRotator CurrentRotation = GetActorRotation();
        
		// 현재 회전에서 목표 회전까지 부드럽게 보간
		FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaSeconds, 3.f);
		SetActorRotation(NewRotation);

		// 다 열렸다면 업데이트 중지
		if (CurrentRotation.Equals(TargetRotation, 0.1f))
		{
			bIsOpened = false;
		}
	}
}
