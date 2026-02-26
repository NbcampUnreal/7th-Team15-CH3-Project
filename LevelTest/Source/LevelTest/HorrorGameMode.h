#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HorrorGameMode.generated.h"




UCLASS()
class LEVELTEST_API AHorrorGameMode : public AGameModeBase
{
	GENERATED_BODY()


public:
	AHorrorGameMode();

	virtual void BeginPlay() override;

#pragma region GameFlowLogic
	void OnPlayerDeath(ACharacter* DeadPlayer);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameProgress")
	int32 CurrentPhase;

#pragma endregion

};
/*
#pragma region SaveLoad

	UFUNCTION(BlueprintCallable, Category = "SaveSystem")
	void SaveGame();

	void LoadGame();

#pragma endregion


*/
