#include "AHCombatComponent.h"

#include "Actor/BaseWeapon.h"
#include "Actor/Character/PlayerCharacter/AHPlayerCharacter.h"
#include "Engine/World.h"

UAHCombatComponent::UAHCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAHCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<AAHPlayerCharacter>(GetOwner());

	QuickbarSlots.Init(nullptr, MaxSlots);
}

void UAHCombatComponent::AddWeaponToQuickbar(TSubclassOf<ABaseWeapon> WeaponClass)
{
	if (!WeaponClass)
	{
		return;
	}

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

void UAHCombatComponent::SwitchWeapon(int32 SlotIndex)
{
	if (!QuickbarSlots.IsValidIndex(SlotIndex))
	{
		return;
	}

	if (EquippedWeapon)
	{
		EquippedWeapon->Destroy();
		EquippedWeapon = nullptr;
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
		}
	}
}

void UAHCombatComponent::EquipWeapon(ABaseWeapon* WeaponToEquip)
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
void UAHCombatComponent::ProcessPrimaryAction()
{
	if (!EquippedWeapon || !Character) return;

	FGameplayTag Tag = EquippedWeapon->WeaponTag;
	// Class Cast <> 내장에서 해쉬...

	if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Tag.Weapon"))))
	{
		FVector CameraLoc; FRotator CameraRot;
		Character->GetController()->GetPlayerViewPoint(CameraLoc, CameraRot);
		EquippedWeapon->Fire(CameraLoc, CameraRot);
		//
	}
	else if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Tag.Consume"))))
	{
		UE_LOG(LogTemp, Warning, TEXT("아이템 사용!"));
	}
	else if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Tag.Melee"))))
	{
	}
	else if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Tag.Extra"))))
	{
	}
}

void UAHCombatComponent::ProcessSecondaryAction(bool bIsPressed)
{
	if (EquippedWeapon)
	{
		EquippedWeapon->SecondaryAction(bIsPressed);
		//base weapon에 SecondaryAction(IsPressed) 
	}
}

void UAHCombatComponent::SpawnDefaultWeapon()
{
	if (Character && DefaultWeaponClass)
	{
		AddWeaponToQuickbar(DefaultWeaponClass);

		SwitchWeapon(0);
	}
}