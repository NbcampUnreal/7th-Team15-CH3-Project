#include "APlayerCharacter.h"
#include"AHPlayerController.h"
#include"GameFramework/SpringArmComponent.h"
#include"Camera/CameraComponent.h"
#include"CharacterStatusComponent.h"
#include"EnhancedInputComponent.h"
#include"GameFramework/CharacterMovementComponent.h"


AAPlayerCharacter::AAPlayerCharacter()
{
 	PrimaryActorTick.bCanEverTick = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	StatusComp = CreateDefaultSubobject<UCharacterStatusComponent>(TEXT("StatusComp"));


	NormalSpeed = 400.f;

	SprintSpeedMultiple = 1.5f;
	SprintSpeed = NormalSpeed * SprintSpeedMultiple;

	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;

	CombatComp = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComp"));
}

void AAPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (StatusComp)
	{
		StatusComp->OnDeath.AddDynamic(this, &AAPlayerCharacter::HandleDeath);
	}
}

void AAPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	AAHPlayerController* PC = Cast<AAHPlayerController>(GetController());
	if (!PC) return;

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (PC->MoveAction)
		{
			EIC->BindAction(PC->MoveAction, ETriggerEvent::Triggered, this, &AAPlayerCharacter::Move);
		}
		if (PC->LookAction)
		{
			EIC->BindAction(PC->LookAction, ETriggerEvent::Triggered, this, &AAPlayerCharacter::Look);
		}
		
		if (PC->JumpAction)
		{
			EIC->BindAction(
				PC->JumpAction,
				ETriggerEvent::Triggered,
				this,
				&AAPlayerCharacter::StartJump
			);

			EIC->BindAction(
				PC->JumpAction,
				ETriggerEvent::Completed,
				this,
				&AAPlayerCharacter::StopJump
			);
		}
		if (PC->SprintAction)
		{
			EIC->BindAction(
				PC->SprintAction,
				ETriggerEvent::Triggered,
				this,
				&AAPlayerCharacter::SprintStart
			);

			EIC->BindAction(
				PC->SprintAction,
				ETriggerEvent::Completed,
				this,
				&AAPlayerCharacter::SprintEnd
			);
		}
		if (PC->PrimeAction)
		{
			EIC->BindAction(
				PC->PrimeAction,
				ETriggerEvent::Completed,
				this,
				&AAPlayerCharacter::OnPrimeAction
			);
		}
		if (PC->SecondAction)
		{
			EIC->BindAction(
				PC->SecondAction,
				ETriggerEvent::Triggered,
				this,
				&AAPlayerCharacter::OnSecondAction
			);
			EIC->BindAction(
				PC->SecondAction,
				ETriggerEvent::Completed,
				this,
				&AAPlayerCharacter::OnSecondAction
			);
		}
		if (PC->Slot1Action)
		{
			EIC->BindAction(
				PC->Slot1Action,
				ETriggerEvent::Triggered,
				this,
				&AAPlayerCharacter::OnSlot1
			);
		}
		if (PC->Slot2Action)
		{
			EIC->BindAction(
				PC->Slot2Action,
				ETriggerEvent::Triggered,
				this,
				&AAPlayerCharacter::OnSlot2
			);
		}
		if (PC->Slot3Action)
		{
			EIC->BindAction(
				PC->Slot3Action,
				ETriggerEvent::Triggered,
				this,
				&AAPlayerCharacter::OnSlot3
			);
		}
		if (PC->Slot4Action)
		{
			EIC->BindAction(
				PC->Slot4Action,
				ETriggerEvent::Triggered,
				this,
				&AAPlayerCharacter::OnSlot4
			);
		}
		if (PC->InteractAction)
		{
			EIC->BindAction(
				PC->InteractAction,
				ETriggerEvent::Triggered,
				this,
				&AAPlayerCharacter::ProcessInteract
			);
		}
	}
	
}

void AAPlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();


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


void AAPlayerCharacter::StartJump(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		Jump();
	}
}

void AAPlayerCharacter::StopJump(const FInputActionValue& Value)
{
	if (!Value.Get<bool>())
	{
		StopJumping();
	}
}

void AAPlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookInput = Value.Get<FVector2D>();

	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}

void AAPlayerCharacter::SprintStart(const FInputActionValue& Value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}

void AAPlayerCharacter::SprintEnd(const FInputActionValue& Value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	}
}

void AAPlayerCharacter::GetDamage(float DamageAmount)
{
	if (StatusComp)
	{
		StatusComp->ApplyDamage(DamageAmount);

		UE_LOG(LogTemp, Warning, TEXT("Player GetDamage Test! %f"), DamageAmount);
	}

}

void AAPlayerCharacter::HandleDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Death"));
	Destroy();
}

void AAPlayerCharacter::OnPrimeAction()
{
	if (CombatComp) CombatComp->ProcessPrimaryAction();
}

void AAPlayerCharacter::OnSecondAction(const FInputActionValue& Value)
{
	bIsAiming = Value.Get<bool>();
	if (CombatComp)
	{
		CombatComp->ProcessSecondaryAction(Value.Get<bool>());
	}
}

void AAPlayerCharacter::OnSlot1()
{
	if (CombatComp) CombatComp->SwitchWeapon(0);
}

void AAPlayerCharacter::OnSlot2()
{
	if (CombatComp) CombatComp->SwitchWeapon(1);
}

void AAPlayerCharacter::OnSlot3()
{
	if (CombatComp) CombatComp->SwitchWeapon(2);
}

void AAPlayerCharacter::OnSlot4()
{
	if (CombatComp) CombatComp->SwitchWeapon(3);
}

void AAPlayerCharacter::ProcessInteract()
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
		if (HitActor && HitActor->Implements<UInteractInterface>())
		{
			float DistanceToCharacter = FVector::Dist(GetActorLocation(), HitActor->GetActorLocation());
			if (DistanceToCharacter <= InteratRange) // 캡슐 기준 유효 범위 체크
			{
				IInteractInterface* Interactable = Cast<IInteractInterface>(HitActor);
				if (Interactable) Interactable->Interact(this);
			}
		}
	}
}