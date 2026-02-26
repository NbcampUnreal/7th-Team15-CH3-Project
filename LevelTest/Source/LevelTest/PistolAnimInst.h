#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PistolAnimInst.generated.h"

UCLASS()
class LEVELTEST_API UPistolAnimInst : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float AimPitch;

	UPROPERTY()
	class AAPlayerCharacter* PlayerCharacter;
};
