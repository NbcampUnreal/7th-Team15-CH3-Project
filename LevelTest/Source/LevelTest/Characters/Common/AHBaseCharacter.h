#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AHBaseCharacter.generated.h"

class UAHCharacterStatusComponent;
class UAnimMontage;

UCLASS()
class LEVELTEST_API AAHBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAHBaseCharacter();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	virtual void HandleDeath();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Status")
	UAHCharacterStatusComponent* StatusComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	UAnimMontage* DamagedMontage;
};
