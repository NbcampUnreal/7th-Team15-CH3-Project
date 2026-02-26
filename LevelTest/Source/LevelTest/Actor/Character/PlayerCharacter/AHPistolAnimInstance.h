#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AHPistolAnimInstance.generated.h"

UCLASS()
class LEVELTEST_API UAHPistolAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float AimPitch;

	UPROPERTY()
	class AAHPlayerCharacter* PlayerCharacter;
};
