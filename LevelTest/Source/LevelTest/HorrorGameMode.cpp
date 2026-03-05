#include "HorrorGameMode.h"
#include"GameFramework/PlayerController.h"
#include"GameFramework/Character.h"
#include"READABLE.h"
#include "EngineUtils.h"

class HorrorSaveGame;

AHorrorGameMode::AHorrorGameMode()
{
	//DefaultPawnClass = APlayerCharacter::StaticClass();
	//PlayerControllerClass = AHPlayerController::StaticClass();
	//GameStateClass = AGameStateBase::StaticClass();

	CurrentPhase = 0;
}


void AHorrorGameMode::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<AREADABLE> It(GetWorld()); It; ++It)
	{
		It->OnNoteReadFinished.AddUObject(this, &AHorrorGameMode::OnNoteProcessed);
	}
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
}

void AHorrorGameMode::OnNoteProcessed(AREADABLE* ReadNote)
{
	CurrentPhase++; // 페이즈 변화,
	OnGlobalPhaseChanged.Broadcast(CurrentPhase);
}


/*
void AHorrorGameMode::SetStoryPhase(int32 NewPhase)
{
	if (CurrentPhase == NewPhase) return;

	CurrentPhase = NewPhase;

	UE_LOG(LogTemp, Warning, TEXT("작동하는지 테스트"));

	/
	* 
	* 
	* 
	*  페이즈별 라이팅 전환, 몬스터 페이즈 변화,
	* 
	* 
	* 
	
}
#pragma endregion
*/

/*
#pragma region SaveLoad

void AHorrorGameMode::SaveGame()
{
	FString SlotName = TEXT("SaveData_Slot");

	HorrorSaveGame* SaveInstance = Cast<UGameplayStatics>(UGameplayStatics::CreateSaveGameObject(HorrorSaveGame::StaticClass()));
	if (SaveInstance)
	{
		SaveInstance->SavedPhase = CurrentPhase;

		UGameplayStatics::SaveGameToSlot(SaveInstance, SlotName, 0);
		UE_LOG(LogTemp, Warning, TEXT("SAVE WORK TEST"));
	}
}

void AHorrorGameMode::LoadGame()
{
	FString SlotName = TEXT("슬롯데이터1");

	if (UGameplayStatics::DoesSaveGameExist(SlotName, 0));
	{
		HorrorSaveGame* LoadInstance = Cast<HorrorSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
		if (LoadInstance)
		{
			CurrentPhase = LoadInstance->SavedPhase;
			UE_LOG(LogTemp, Log, TEXT("LOAD TEST WORKED"));
		}
	}

}

#pragma endregion
*/

