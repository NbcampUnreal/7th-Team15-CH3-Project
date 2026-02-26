#include "HorrorGameMode.h"
#include"GameFramework/PlayerController.h"
#include"GameFramework/Character.h"

class HorrorSaveGame;

AHorrorGameMode::AHorrorGameMode()
{
	CurrentPhase = 0;
}


void AHorrorGameMode::BeginPlay()
{
	Super::BeginPlay();

}

#pragma region GameFlowLogic

void AHorrorGameMode::OnPlayerDeath(ACharacter* DeadPlayer)
{
	if (!DeadPlayer) return;

	UE_LOG(LogTemp, Error, TEXT("Player Dead Check"));

	APlayerController* PC = Cast<APlayerController>(DeadPlayer->GetController());
	if (PC)
	{
		DeadPlayer->DisableInput(PC);
		PC->bShowMouseCursor = true;
		PC->SetInputMode(FInputModeUIOnly());
	}

	// 죽은 상태 UI 출력! 나아아아중에 작성해야핢!
}
