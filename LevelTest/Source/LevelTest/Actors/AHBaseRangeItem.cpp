#include "Actors/AHBaseRangeItem.h"
#include "Characters/Player/AHPlayerCharacter.h"

void AAHBaseRangeItem::StartPrimeAction()
{
	
	Fire();
}


void AAHBaseRangeItem::Fire()
{
	AAHPlayerCharacter* PlayerCharacter = GetPlayerOwner();
	if (PlayerCharacter != nullptr && PlayerCharacter->GetController() != nullptr)
	{
		FVector CameraLoc;
		FRotator CameraRot;
		PlayerCharacter-> GetController()->GetPlayerViewPoint(CameraLoc, CameraRot);
		
		FVector TraceEnd = CameraLoc + (CameraRot.Vector() * TraceRange);
		
		FHitResult Hit;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(PlayerCharacter);
		
		bool bHit = GetWorld()->LineTraceSingleByChannel(Hit,CameraLoc,TraceEnd,ECC_Visibility,Params);
			
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f, 0, 1.0f);
		
		// 발사 이펙트
		
		if (bHit)
		{
			// 이펙트
		}
		
		AActor* HitActor = Hit.GetActor();
		if (UAHCharacterStatusComponent* HitComp = Cast<UAHCharacterStatusComponent>(HitActor))
		{
			if (HitComp)
			{
				HitComp->ApplyDamage(Damage);
			}
		}
	}
}
