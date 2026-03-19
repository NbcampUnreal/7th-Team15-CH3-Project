#include "AHGameMode.h"
#include"GameFramework/PlayerController.h"
#include"GameFramework/Character.h"
#include"World/READABLE.h"
#include "EngineUtils.h"

class HorrorSaveGame;

AAHGameMode::AAHGameMode()
{
	//DefaultPawnClass = APlayerCharacter::StaticClass();
	//PlayerControllerClass = AHPlayerController::StaticClass();
	//GameStateClass = AGameStateBase::StaticClass();

	CurrentPhase = 0;
}


void AAHGameMode::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<AREADABLE> It(GetWorld()); It; ++It)
	{
		It->OnNoteReadFinished.AddUObject(this, &AAHGameMode::OnNoteProcessed);
	}
}

void AAHGameMode::OnPlayerDeath(ACharacter* DeadPlayer)
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

void AAHGameMode::OnNoteProcessed(AREADABLE* ReadNote)
{
	CurrentPhase++; // 페이즈 변화,
	OnGlobalPhaseChanged.Broadcast(CurrentPhase);
}

