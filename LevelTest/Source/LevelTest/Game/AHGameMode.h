#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AHGameMode.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGlobalPhaseChanged, int32 NewPhase);

UCLASS()
class LEVELTEST_API AAHGameMode : public AGameModeBase
{
	GENERATED_BODY()


public:
	AAHGameMode();
	
	virtual void BeginPlay() override;

	FOnGlobalPhaseChanged OnGlobalPhaseChanged;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameProgress")
	int32 CurrentPhase;

protected:
// 서브시스템으로 옮겼다 
	
};