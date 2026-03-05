#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HorrorGameMode.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGlobalPhaseChanged, int32 NewPhase);

UCLASS()
class LEVELTEST_API AHorrorGameMode : public AGameModeBase
{
	GENERATED_BODY()


public:
	AHorrorGameMode();

	virtual void BeginPlay() override;

	FOnGlobalPhaseChanged OnGlobalPhaseChanged;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameProgress")
	int32 CurrentPhase;

#pragma region GameFlowLogic
	void OnPlayerDeath(ACharacter* DeadPlayer);

protected:

	void OnNoteProcessed(class AREADABLE* ReadNote);
#pragma endregion

};
/*
#pragma region SaveLoad

	UFUNCTION(BlueprintCallable, Category = "SaveSystem")
	void SaveGame();

	void LoadGame();

#pragma endregion


*/
