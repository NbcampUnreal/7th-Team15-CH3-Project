#include "AHPlayerCharacter.h"
#include"Characters/Controller/AHPlayerController.h"
#include"GameFramework/SpringArmComponent.h"
#include"Camera/CameraComponent.h"
#include"Characters/Components/AHCharacterStatusComponent.h"
#include"EnhancedInputComponent.h"
#include"GameFramework/CharacterMovementComponent.h"
#include "Subsystem/AHGameInstanceSubsystem.h"

AAHPlayerCharacter::AAHPlayerCharacter()
{
 	PrimaryActorTick.bCanEverTick = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	StatusComp = CreateDefaultSubobject<UAHCharacterStatusComponent>(TEXT("StatusComp"));

	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	
	CombatComp = CreateDefaultSubobject<UAHCombatComponent>(TEXT("CombatComp"));

}

void AAHPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
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
		if (PC->PrimeAction)
		{
			EIC->BindAction(PC->PrimeAction,ETriggerEvent::Completed,this,&AAHPlayerCharacter::OnPrimeAction);
		}
		if (PC->SecondAction)
		{
			EIC->BindAction(PC->SecondAction,ETriggerEvent::Triggered,this,&AAHPlayerCharacter::OnSecondAction);
			EIC->BindAction(PC->SecondAction,ETriggerEvent::Completed,this,&AAHPlayerCharacter::OnSecondAction);
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

void AAHPlayerCharacter::OnPrimeAction()
{
	if (CombatComp)
	{
		CombatComp->ProcessPrimaryAction();
	}
}

void AAHPlayerCharacter::OnSecondAction(const FInputActionValue& Value)
{
	bIsAiming = Value.Get<bool>();
	if (CombatComp)
	{
		CombatComp->ProcessSecondaryAction(Value.Get<bool>());
	}
}

void AAHPlayerCharacter::OnSlot1()
{
	if (CombatComp)
	{
		CombatComp->SwitchWeapon(0);
	}
}

void AAHPlayerCharacter::OnSlot2()
{
	if (CombatComp)
	{
		CombatComp->SwitchWeapon(1);
	}
}

void AAHPlayerCharacter::OnSlot3()
{
	if (CombatComp)
	{
		CombatComp->SwitchWeapon(2);
	}
}

void AAHPlayerCharacter::OnSlot4()
{
	if (CombatComp)
	{ 
		CombatComp->SwitchWeapon(3);
	}
}

void AAHPlayerCharacter::OnReload()
{
	if (CombatComp)
	{
		CombatComp->Reload();
	}
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

void AAHPlayerCharacter::UpdateAmmoUI(int32 CurrentAmmo, int32 SpareAmmo)
{
	if (UAHGameInstanceSubsystem* GameInstance = GetGameInstance()->GetSubsystem<UAHGameInstanceSubsystem>())
	{
		GameInstance->OnAmmoChanged.Broadcast(CurrentAmmo,SpareAmmo);
	}
}

void AAHPlayerCharacter::UpdateCrosshairVisibility(bool bIsWeaponEquipped)
{
	if (UAHGameInstanceSubsystem* GameInstance = GetGameInstance()->GetSubsystem<UAHGameInstanceSubsystem>())
	{
		//GameInstance-> On~~  이게 캐릭터에 있는게 맞나?
		// 무기에 붙이는게 맞지 않나?
	}
}

void AAHPlayerCharacter::ShowGameMessage(FString Message, bool bShow)
{
	if (UAHGameInstanceSubsystem* GameInstance = GetGameInstance()->GetSubsystem<UAHGameInstanceSubsystem>())
	{
		GameInstance->OnDisplay.Broadcast(Message,bShow);
	}
}
