#include "CombatComponent.h"
#include "BaseWeapon.h"
#include "APlayerCharacter.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "AHPlayerController.h"
#include"CharacterStatusComponent.h"
#include "AHMainWidget.h"
#include "AHHUD.h"


UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<AAPlayerCharacter>(GetOwner());

	QuickbarSlots.Init(nullptr, MaxSlots);

	SlotAmmoCounts.Init(-1, MaxSlots);
}

void UCombatComponent::SpawnDefaultWeapon()
{
	if (Character && DefaultWeaponClass)
	{
		AddWeaponToQuickbar(DefaultWeaponClass);
	}
}

void UCombatComponent::AddWeaponToQuickbar(TSubclassOf<ABaseWeapon> WeaponClass)
{
	if (!WeaponClass) return;

	for (int32 i = 0; i < MaxSlots; i++)
	{
		if (QuickbarSlots[i] == nullptr)
		{
			QuickbarSlots[i] = WeaponClass;
			UE_LOG(LogTemp, Warning, TEXT("Weapon Class Added to Slot %d"), i);

			SwitchWeapon(i);
			//무기 줍자마자 장착

			return;
		}
	}
}


void UCombatComponent::SwitchWeapon(int32 SlotIndex)
{
	if (!QuickbarSlots.IsValidIndex(SlotIndex))
	{
		return;
	}

	if (EquippedWeapon)
	{
		SlotAmmoCounts[CurrentSlotIndex] = EquippedWeapon->CurrentAmmo;

		if (Character && EquippedWeapon->WeaponTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Tag.Weapon"))))
		{
			Character->UpdateCrosshairVisibility(false);
		}

		EquippedWeapon->Destroy();
		EquippedWeapon = nullptr;

		if (CurrentSlotIndex == SlotIndex)
		{
			CurrentSlotIndex = -1;
			return;
		}

	}

	if (QuickbarSlots[SlotIndex] != nullptr)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = Character;
		SpawnParams.Instigator = Character;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FVector SpawnLoc = Character->GetMesh()->GetSocketLocation(FName("HandGrip_R"));
		FRotator SpawnRot = Character->GetMesh()->GetSocketRotation(FName("HandGrip_R"));

		EquippedWeapon = GetWorld()->SpawnActor<ABaseWeapon>(QuickbarSlots[SlotIndex], SpawnLoc, SpawnRot, SpawnParams);

		if (EquippedWeapon)
		{
			EquipWeapon(EquippedWeapon);
			CurrentSlotIndex = SlotIndex;

			if (SlotAmmoCounts[SlotIndex] != -1)
			{
				EquippedWeapon->CurrentAmmo = SlotAmmoCounts[SlotIndex];
			}
			else
			{
				EquippedWeapon->CurrentAmmo = EquippedWeapon->MaxAmmo;
				UE_LOG(LogTemp, Warning, TEXT("New Weapon Spawned: 0 Ammo"));
			}

			if (EquippedWeapon->WeaponTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Tag.Weapon"))))
			{
				Character->UpdateCrosshairVisibility(true);
			}

			Character->UpdateAmmoUI(EquippedWeapon->CurrentAmmo, SpareAmmo);
		}
	}
}

void UCombatComponent::EquipWeapon(ABaseWeapon* WeaponToEquip)
{
	if (!WeaponToEquip || !Character) return;

	WeaponToEquip->SetActorHiddenInGame(false);

	if (WeaponToEquip->GetStaticMeshComp())
	{
		WeaponToEquip->GetStaticMeshComp()->SetSimulatePhysics(false);
		WeaponToEquip->GetStaticMeshComp()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		WeaponToEquip->GetStaticMeshComp()->SetVisibility(false);
	}

	if (WeaponToEquip->GetWeaponMesh())
	{
		WeaponToEquip->GetWeaponMesh()->SetSimulatePhysics(false);
		WeaponToEquip->GetWeaponMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		WeaponToEquip->GetWeaponMesh()->SetVisibility(true);
	}

	bool bAttached = WeaponToEquip->AttachToComponent(
		Character->GetMesh(),
		FAttachmentTransformRules::SnapToTargetIncludingScale,
		FName("HandGrip_R")
		//소켓 부착
	);

	if (bAttached)
	{
		WeaponToEquip->SetActorRelativeLocation(FVector::ZeroVector);
		WeaponToEquip->SetActorRelativeRotation(FRotator::ZeroRotator);
	}
}
void UCombatComponent::ProcessPrimaryAction()
{
	if (bIsReloading || !EquippedWeapon || !Character) return;

	FGameplayTag Tag = EquippedWeapon->WeaponTag;

	if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Tag.Weapon"))))
	{
		FVector CameraLoc; FRotator CameraRot;
		Character->GetController()->GetPlayerViewPoint(CameraLoc, CameraRot);
		if (EquippedWeapon->CurrentAmmo == 0)
		{
			EquippedWeapon->PlayEmptySound();
		}
		else 
		{
			EquippedWeapon->Fire(CameraLoc, CameraRot);
			EquippedWeapon->CurrentAmmo--;
			if (Character->GetMainWidget())
			{
				Character->GetMainWidget()->UpdateCrosshairSpread(0.2f);
			}
		}
		Character->UpdateAmmoUI(EquippedWeapon->CurrentAmmo, SpareAmmo);
	}
	else if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Tag.Consume"))))
	{
		if (Character && Character->StatusComp)
		{
			Character->StatusComp->Heal(30.f);
		}

		// 2. 소모품 개수 감소 및 퀵바에서 제거 로직
		EquippedWeapon->CurrentAmmo--;
		if (EquippedWeapon->CurrentAmmo <= 0)
		{
			// 아이템 다 썼으면 퀵바에서 비우기 처리
			QuickbarSlots[CurrentSlotIndex] = nullptr;
			EquippedWeapon->Destroy();
			EquippedWeapon = nullptr;
		}
	}
	else if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Tag.Melee"))))
	{
	}
	else if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Tag.Key"))))
	{
	}
}

void UCombatComponent::ProcessSecondaryAction(bool bIsPressed)
{
	if (EquippedWeapon)
	{
		EquippedWeapon->SecondaryAction(bIsPressed);
		//base weapon에 SecondaryAction(IsPressed) 
	}
}

void UCombatComponent::Reload()
{
	if (bIsReloading || !EquippedWeapon || SpareAmmo <= 0) return;

	int32 AmmoNeeded = EquippedWeapon->MaxAmmo - EquippedWeapon->CurrentAmmo;
	if (AmmoNeeded <= 0) return;

	bIsReloading = true;
	
	GetWorld()->GetTimerManager().SetTimer(
		ReloadTimerHandle,
		this,
		&UCombatComponent::FinishReloading,
		2.0f,
		false
	);
}

void UCombatComponent::FinishReloading()
{
	if (EquippedWeapon)
	{
		int32 AmmoNeeded = EquippedWeapon->MaxAmmo - EquippedWeapon->CurrentAmmo;
		int32 ReloadAmount = FMath::Min(AmmoNeeded, SpareAmmo);

		EquippedWeapon->CurrentAmmo += ReloadAmount;
		SpareAmmo -= ReloadAmount;

		Character->UpdateAmmoUI(EquippedWeapon->CurrentAmmo, SpareAmmo);
	}

	bIsReloading = false;

}
