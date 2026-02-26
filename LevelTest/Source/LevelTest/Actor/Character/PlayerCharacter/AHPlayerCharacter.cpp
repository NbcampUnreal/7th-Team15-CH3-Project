#include "AHPlayerCharacter.h"
#include"AHPlayerController.h"
#include"GameFramework/SpringArmComponent.h"
#include"Camera/CameraComponent.h"
#include"EnhancedInputComponent.h"
#include "Actor/Character/Component/AHCharacterStatusComponent.h"
#include "Actor/Character/Component/AHCombatComponent.h"
#include"GameFramework/CharacterMovementComponent.h"


AAHPlayerCharacter::AAHPlayerCharacter()
{
 	PrimaryActorTick.bCanEverTick = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	StatusComp = CreateDefaultSubobject<UAHCharacterStatusComponent>(TEXT("StatusComp"));


	NormalSpeed = 400.f;

	SprintSpeedMultiple = 1.5f;
	SprintSpeed = NormalSpeed * SprintSpeedMultiple;

	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;

	CombatComp = CreateDefaultSubobject<UAHCombatComponent>(TEXT("CombatComp"));
}

void AAHPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (StatusComp)
	{
		StatusComp->OnDeath.AddDynamic(this, &AAHPlayerCharacter::HandleDeath);
	}
}

void AAHPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	AAHPlayerController* PC = Cast<AAHPlayerController>(GetController());
	if (!PC) return;

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	if (!EIC)
	{
		return;
	}
	
	if (PC->MoveAction)
	{
		EIC->BindAction(PC->MoveAction, ETriggerEvent::Triggered, this, &AAHPlayerCharacter::Move);
	}
	if (PC->LookAction)
	{
		EIC->BindAction(PC->LookAction, ETriggerEvent::Triggered, this, &AAHPlayerCharacter::Look);
	}
		
	if (PC->JumpAction)
	{
		EIC->BindAction(
			PC->JumpAction,
			ETriggerEvent::Triggered,
			this,
			&AAHPlayerCharacter::StartJump
		);

		EIC->BindAction(
			PC->JumpAction,
			ETriggerEvent::Completed,
			this,
			&AAHPlayerCharacter::StopJump
		);
	}
	if (PC->SprintAction)
	{
		EIC->BindAction(
			PC->SprintAction,
			ETriggerEvent::Triggered,
			this,
			&AAHPlayerCharacter::SprintStart
		);

		EIC->BindAction(
			PC->SprintAction,
			ETriggerEvent::Completed,
			this,
			&AAHPlayerCharacter::SprintEnd
		);
	}
	if (PC->PrimeAction)
	{
		EIC->BindAction(
			PC->PrimeAction,
			ETriggerEvent::Completed,
			this,
			&AAHPlayerCharacter::OnPrimeAction
		);
	}
	if (PC->SecondAction)
	{
		EIC->BindAction(
			PC->SecondAction,
			ETriggerEvent::Triggered,
			this,
			&AAHPlayerCharacter::OnSecondAction
		);
		EIC->BindAction(
			PC->SecondAction,
			ETriggerEvent::Completed,
			this,
			&AAHPlayerCharacter::OnSecondAction
		);
	}
	if (PC->Slot1Action)
	{
		EIC->BindAction(
			PC->Slot1Action,
			ETriggerEvent::Triggered,
			this,
			&AAHPlayerCharacter::OnSlot1
		);
	}
	if (PC->Slot2Action)
	{
		EIC->BindAction(
			PC->Slot2Action,
			ETriggerEvent::Triggered,
			this,
			&AAHPlayerCharacter::OnSlot2
		);
	}
	if (PC->Slot3Action)
	{
		EIC->BindAction(
			PC->Slot3Action,
			ETriggerEvent::Triggered,
			this,
			&AAHPlayerCharacter::OnSlot3
		);
	}
	if (PC->Slot4Action)
	{
		EIC->BindAction(
			PC->Slot4Action,
			ETriggerEvent::Triggered,
			this,
			&AAHPlayerCharacter::OnSlot4
		);
	}
	if (PC->InteractAction)
	{
		EIC->BindAction(
			PC->InteractAction,
			ETriggerEvent::Triggered,
			this,
			&AAHPlayerCharacter::ProcessInteract
		);
	}
}

void AAHPlayerCharacter::Move(const FInputActionValue& Value)
{
	if (!Controller) return;

	const FVector2D MoveInput = Value.Get<FVector2D>();

	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		AddMovementInput(GetActorForwardVector(), MoveInput.X);
	}

	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddMovementInput(GetActorRightVector(), MoveInput.Y);
	}
}


void AAHPlayerCharacter::StartJump(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		Jump();
	}
}

void AAHPlayerCharacter::StopJump(const FInputActionValue& Value)
{
	if (!Value.Get<bool>())
	{
		StopJumping();
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
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}

void AAHPlayerCharacter::SprintEnd(const FInputActionValue& Value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	}
}

void AAHPlayerCharacter::GetDamage(float DamageAmount)
{
	if (StatusComp)
	{
		StatusComp->ApplyDamage(DamageAmount);

		UE_LOG(LogTemp, Warning, TEXT("Player GetDamage Test! %f"), DamageAmount);
	}

}

void AAHPlayerCharacter::HandleDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Death"));
	Destroy();
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
	if (CombatComp) CombatComp->SwitchWeapon(0);
}

void AAHPlayerCharacter::OnSlot2()
{
	if (CombatComp) CombatComp->SwitchWeapon(1);
}

void AAHPlayerCharacter::OnSlot3()
{
	if (CombatComp) CombatComp->SwitchWeapon(2);
}

void AAHPlayerCharacter::OnSlot4()
{
	if (CombatComp) CombatComp->SwitchWeapon(3);
}

void AAHPlayerCharacter::ProcessInteract()
{
	FVector Start = CameraComp->GetComponentLocation();
	FVector End = Start + (CameraComp->GetForwardVector() * InteratRange);
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
			if (DistanceToCharacter <= InteratRange) // 캡슐 기준 유효 범위 체크
			{
				if (IAHInteractInterface* Interactable = Cast<IAHInteractInterface>(HitActor))
				{
					Interactable->Interact(this);
				}
			}
		}
	}
}