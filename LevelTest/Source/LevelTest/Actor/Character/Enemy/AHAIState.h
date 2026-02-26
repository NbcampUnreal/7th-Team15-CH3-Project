#pragma once

#include "CoreMinimal.h"
#include "AHAIState.generated.h"

UENUM(BlueprintType)
enum class EAHEnemyState : uint8
{
    Idle          UMETA(DisplayName = "Idle"),
    Patrol        UMETA(DisplayName = "Patrol"),
    Investigate   UMETA(DisplayName = "Investigate"),
    Chase         UMETA(DisplayName = "Chase"),
    Attack        UMETA(DisplayName = "Attack"),
    Downed        UMETA(DisplayName = "Attack"),
    Rage          UMETA(DisplayName = "Attack")
};

namespace BBKeys
{
    const FName TargetActor = TEXT("TargetActor");
    const FName TargetLocation = TEXT("TargetLocation");
    const FName EnemyState = TEXT("EnemyState");
    const FName PatrolLocation = TEXT("PatrolLocation");
}

//test
