#include "AHPlayerCharacter.h"
#include"Characters/Controller/AHPlayerController.h"
#include"GameFramework/SpringArmComponent.h"
#include"Camera/CameraComponent.h"
#include"Characters/Components/AHCharacterStatusComponent.h"
#include"EnhancedInputComponent.h"
#include "Actors/AHBaseItems/AHBaseItem.h"
#include "Characters/Components/AHInventoryComponent.h"
#include"GameFramework/CharacterMovementComponent.h"
#include "Subsystem/EventSubsystem.h"
#include "AHItemData.h"

AAHPlayerCharacter::AAHPlayerCharacter()
{
 	PrimaryActorTick.bCanEverTick = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	StatusComp = CreateDefaultSubobject<UAHCharacterStatusComponent>(TEXT("StatusComp"));
	InventoryComp = CreateDefaultSubobject<UAHInventoryComponent>(TEXT("InventoryComp"));

	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	
}

void AAHPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (UEventSubsystem* Eventsys = UEventSubsystem::Get(this))
	{
		Eventsys->OnEquipRequest.AddDynamic(this, &AAHPlayerCharacter::HandleEquipRequest);
	}
}

void AAHPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	AAHPlayerController* PC = Cast<AAHPlayerController>(GetController());
	if (PC == nullptr)
	{
		return;
	}
	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EIC != nullptr)
	{
		if (PC->MoveAction)
		{
			EIC->BindAction(PC->MoveAction, ETriggerEvent::Triggered, this, &AAHPlayerCharacter::InputMove);
		}
		if (PC->LookAction)
		{
			EIC->BindAction(PC->LookAction, ETriggerEvent::Triggered, this, &AAHPlayerCharacter::Look);
		}
		
		if (PC->JumpAction)
		{
			EIC->BindAction(PC->JumpAction,ETriggerEvent::Started,this,&AAHPlayerCharacter::OnInputJump);
		}
		if (PC->SprintAction)
		{
			EIC->BindAction(PC->SprintAction,ETriggerEvent::Triggered,this,&AAHPlayerCharacter::SprintStart);

			EIC->BindAction(PC->SprintAction,ETriggerEvent::Completed,this,&AAHPlayerCharacter::SprintEnd);
		}
		if (PC->StartPrimeAction)
		{
			EIC->BindAction(PC->EndPrimeAction,ETriggerEvent::Completed,this,&AAHPlayerCharacter::EndPrimeAction);
			EIC->BindAction(PC->StartPrimeAction, ETriggerEvent::Started, this, &AAHPlayerCharacter::StartPrimeAction);
		}
		if (PC->SecondAction)
		{
			EIC->BindAction(PC->SecondAction,ETriggerEvent::Started,this,&AAHPlayerCharacter::OnSecondAction);
		}
		if (PC->Slot1Action)
		{
			EIC->BindAction(PC->Slot1Action,ETriggerEvent::Completed,this,&AAHPlayerCharacter::OnSlot1);
		}
		if (PC->Slot2Action)
		{
			EIC->BindAction(PC->Slot2Action,ETriggerEvent::Completed,this,&AAHPlayerCharacter::OnSlot2);
		}
		if (PC->Slot3Action)
		{
			EIC->BindAction(PC->Slot3Action,ETriggerEvent::Completed,this,&AAHPlayerCharacter::OnSlot3);
		}
		if (PC->Slot4Action)
		{
			EIC->BindAction(PC->Slot4Action,ETriggerEvent::Completed,this,&AAHPlayerCharacter::OnSlot4);
		}
		if (PC->InteractAction)
		{
			EIC->BindAction(PC->InteractAction, ETriggerEvent::Triggered,this, &AAHPlayerCharacter::ProcessInteract);
		}
		if (PC->ReloadAction)
		{
			EIC->BindAction(PC->ReloadAction,ETriggerEvent::Completed,this,&AAHPlayerCharacter::OnReload);
		}
	}
	
}


void AAHPlayerCharacter::InputMove(const FInputActionValue& Value)
{
	if (Controller == nullptr)
	{
		return;
	}
	const FVector2D MoveInput = Value.Get<FVector2D>();

	if (FMath::IsNearlyZero(MoveInput.X) == false)
	{
		AddMovementInput(GetActorForwardVector(), MoveInput.X);
	}

	if (FMath::IsNearlyZero(MoveInput.Y) == false)
	{
		AddMovementInput(GetActorRightVector(), MoveInput.Y);
	}
}


void AAHPlayerCharacter::OnInputJump(const FInputActionInstance& InputActionInstance)
{
	switch (InputActionInstance.GetTriggerEvent())
	{
	case ETriggerEvent::Started:Jump();
		break;

	case ETriggerEvent::Completed:StopJumping();
		break;

	default:
		break;
	}
}

void AAHPlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookInput = Value.Get<FVector2D>();

	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}

void AAHPlayerCharacter::SprintStart(const FInputActionValue& Value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = OriginalWalkSpeed* SprintSpeedMultiply;
	}
}

void AAHPlayerCharacter::SprintEnd(const FInputActionValue& Value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = OriginalWalkSpeed;
	}
}

//get damage 있던 곳;;;
/*
void AAHPlayerCharacter::HandleDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Death"));
	Destroy();
}
*/

void AAHPlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (GetCharacterMovement())
	{
		OriginalWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	}
}

void AAHPlayerCharacter::EndPrimeAction()
{
	if (EquippedItem == nullptr)
	{
		return;
	}
	EquippedItem->EndPrimeAction();
}

void AAHPlayerCharacter::StartPrimeAction()
{
	if (EquippedItem == nullptr)
	{
		return;
	}
	EquippedItem->StartPrimeAction();
}

void AAHPlayerCharacter::OnSecondAction(const FInputActionValue& Value)
{
	if (EquippedItem == nullptr)
	{
		return;
	}
	EquippedItem->StartSecondaryAction();
}

void AAHPlayerCharacter::OnSlot1()
{
	if (InventoryComp)
	{
		InventoryComp->RequestEquipByIndex(1);
	}
}

void AAHPlayerCharacter::OnSlot2()
{
	if (InventoryComp)
	{
		InventoryComp->RequestEquipByIndex(2);
	}
}

void AAHPlayerCharacter::OnSlot3()
{
	if (InventoryComp)
	{
		InventoryComp->RequestEquipByIndex(3);
	}
}

void AAHPlayerCharacter::OnSlot4()
{
	if (InventoryComp)
	{
		InventoryComp->RequestEquipByIndex(4);
	}
}

void AAHPlayerCharacter::OnReload()
{
	if (EquippedItem == nullptr)
	{
		return;
	}
	//EquippedItem->Reload()
}

void AAHPlayerCharacter::ProcessInteract()
{
	FVector Start = CameraComp->GetComponentLocation();
	FVector End = Start + (CameraComp->GetForwardVector() * InteractRange);
	//카메라 기준

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params))
	{ //카메라 기준 라인트레이싱 발사,
		AActor* HitActor = HitResult.GetActor();
		if (HitActor && HitActor->Implements<UAHInteractInterface>())
		{
			float DistanceToCharacter = FVector::Dist(GetActorLocation(), HitActor->GetActorLocation());
			if (DistanceToCharacter <= InteractRange) // 캡슐 기준 유효 범위 체크
			{
				IAHInteractInterface* Interactable = Cast<IAHInteractInterface>(HitActor);
				if (Interactable) Interactable->Interact(this);
			}
		}
	}
}

void AAHPlayerCharacter::HandleEquipRequest(UAHItemData* ItemData, int32 SlotIndex)
{
	if (ItemData == nullptr)
	{
		return;
	}
	if (CurrentSlotIndex == SlotIndex)
	{
		UnequipCurrentItem();
		return;
	}
	if (EquippedItem)
	{
		UnequipCurrentItem();
	}
	ExecuteEquip(ItemData, SlotIndex);
}

void AAHPlayerCharacter::ExecuteEquip(UAHItemData* ItemData, int32 SlotIndex)
{
	if (ItemData == nullptr || ItemData->ItemClass == nullptr)
	{
		return;
	}
	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.Instigator = this;
	
	EquippedItem = GetWorld()->SpawnActor<AAHBaseItem>(ItemData->ItemClass, Params);
	if (EquippedItem)
	{
		//SnapToTargetIncludingScale: 아이템의 현재 위치를 무시하고, 부착될 대상(소켓)의 위치와 회전값에 딱 붙인다.
		//FName("HandGrip_R") 소켓 지정
		EquippedItem->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale,FName("HandGrip_R"));
		
		CurrentSlotIndex = SlotIndex;
	}
}

void AAHPlayerCharacter::UnequipCurrentItem()
{
	if (EquippedItem)
	{
		EquippedItem->Destroy();
		EquippedItem = nullptr;
	}
	CurrentSlotIndex = -1;
}

/*
void AAHPlayerCharacter::UpdateAmmoUI(int32 CurrentAmmo, int32 SpareAmmo)
{
	if (UEventSubsystem* GameInstance = GetGameInstance()->GetSubsystem<UEventSubsystem>())
	{
		GameInstance->OnAmmoChanged.Broadcast(CurrentAmmo,SpareAmmo);
	}
}

void AAHPlayerCharacter::UpdateCrosshairVisibility(bool bIsWeaponEquipped)
{
	if (UEventSubsystem* GameInstance = GetGameInstance()->GetSubsystem<UEventSubsystem>())
	{
		//GameInstance-> On~~  이게 캐릭터에 있는게 맞나?
		// 무기에 붙이는게 맞지 않나?
	}
}

void AAHPlayerCharacter::ShowGameMessage(FString Message, bool bShow)
{
	if (UEventSubsystem* GameInstance = GetGameInstance()->GetSubsystem<UEventSubsystem>())
	{
		GameInstance->OnDisplay.Broadcast(Message,bShow);
	}
}
*/
