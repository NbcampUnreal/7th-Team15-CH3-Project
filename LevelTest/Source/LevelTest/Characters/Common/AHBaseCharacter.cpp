#include "AHBaseCharacter.h"

#include "Characters/Components/AHCharacterStatusComponent.h"


// Sets default values
AAHBaseCharacter::AAHBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	StatusComp = CreateDefaultSubobject<UAHCharacterStatusComponent>(TEXT("StatusComp"));
}

//DamageAmount 순수뎀지, struct FDamageEvent const& DamageEvent 데미지 이벤트 , EventInstigator 데미지 주동자, DamageCauser 데미지의 원인(총알이라든가 )
float AAHBaseCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	if (StatusComp && DamageAmount > 0.f)
	{
		StatusComp->ApplyDamage(DamageAmount);
	}
	return DamageAmount;
}

void AAHBaseCharacter::HandleDeath()
{
	//공백으로 놓고 이후 자식클래스에서 재정의 override
}


