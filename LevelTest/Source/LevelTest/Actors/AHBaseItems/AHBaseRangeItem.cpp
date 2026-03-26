#include "Actors/AHBaseItems/AHBaseRangeItem.h"

#include "Characters/Common/AHBaseCharacter.h"
#include "Characters/Player/AHPlayerCharacter.h"
#include "Engine/DamageEvents.h"
#include "Subsystem/EventSubsystem.h"

void AAHBaseRangeItem::StartPrimeAction()
{
	if (CurrentAmmo > 0)
	{
		Fire();
		CurrentAmmo--;	
		if (auto* EventSys = UEventSubsystem::Get(this))
		{
			EventSys->OnAmmoChanged.Broadcast(CurrentAmmo, MaxAmmo); 
			//MaxAmmo를 어디서 구현해야할지 고민, 이벤트서브시스템이냐 플레이어컨트롤러냐 
		}
	}	
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
			
		DrawDebugLine(GetWorld(), CameraLoc, TraceEnd, FColor::Red, false, 1.0f, 0, 1.0f);
		
		// 발사 이펙트
		if (bHit)
		{
			// 이펙트
		}
		
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			AAHBaseCharacter* HitCharacter = Cast<AAHBaseCharacter>(HitActor);
			if (HitCharacter != nullptr)
			{
				FDamageEvent GenericDamageEvent;
				HitCharacter->TakeDamage(Damage, GenericDamageEvent, PlayerCharacter->GetController(),this);
			}
		}
	}
}
