#include "AHGameMode.h"
#include"GameFramework/PlayerController.h"

class HorrorSaveGame;

AAHGameMode::AAHGameMode()
{

	CurrentPhase = 0;
}


void AAHGameMode::BeginPlay()
{
	Super::BeginPlay();
	
}


/*
*void AAHGameMode::OnPlayerDeath(ACharacter* DeadPlayer)
{
	if (DeadPlayer == nullptr) return;

	UE_LOG(LogTemp, Error, TEXT("Player Dead Check"));

	APlayerController* PC = Cast<APlayerController>(DeadPlayer->GetController());
	if (PC)
	{
		DeadPlayer->DisableInput(PC);
		PC->bShowMouseCursor = true;
		PC->SetInputMode(FInputModeUIOnly());
	}
}
 서브시스템 이적 진행중
 
 */