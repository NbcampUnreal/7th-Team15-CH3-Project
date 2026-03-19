#include "AHPlayerCharacter.h"
#include"Controller/AHPlayerController.h"
#include"GameFramework/SpringArmComponent.h"
#include"Camera/CameraComponent.h"
#include"Component/AHCharacterStatusComponent.h"
#include"EnhancedInputComponent.h"
#include"GameFramework/CharacterMovementComponent.h"
#include"Kismet/GameplayStatics.h"
#include "World/AHPhasePostProcess.h"
#include "UI/AHHUD.h"
#include"UI/AHMainWidget.h"

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

	if (!StatusComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("NO StatusCOmp Now"));
		StatusComp = FindComponentByClass<UAHCharacterStatusComponent>();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("StatusCOmp Now"));
	}

	if (AAHPlayerController* PC = Cast<AAHPlayerController>(GetController()))
	{
		if (AAHHUD* HUD = PC->GetHUD<AAHHUD>())
		{
			MainWidget = HUD->GetMainWidget();
		}
	}

	if (StatusComp)
	{
		StatusComp->OnDeath.AddDynamic(this, &AAHPlayerCharacter::HandleDeath);
	}
	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAHPhasePostProcess::StaticClass(), FoundActors);
	// 월드에 있는 페이즈 포스트 프로세스 클래스들을 FoundActors Array에 저장,

	if (FoundActors.Num() > 0)
	{
		PostProcessHandler = Cast<AAHPhasePostProcess>(FoundActors[0]);
	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("Fail: PostProcessHandler NOT Found in Level!"));
	}
	//복수의 페이즈포스트프로세스가 있다면 0순위를 핸들러로 사용한다
}

void AAHPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	AAHPlayerController* PC = Cast<AAHPlayerController>(GetController());
	if (!PC) return;

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
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
				ETriggerEvent::Completed,
				this,
				&AAHPlayerCharacter::OnSlot1
			);
		}
		if (PC->Slot2Action)
		{
			EIC->BindAction(
				PC->Slot2Action,
				ETriggerEvent::Completed,
				this,
				&AAHPlayerCharacter::OnSlot2
			);
		}
		if (PC->Slot3Action)
		{
			EIC->BindAction(
				PC->Slot3Action,
				ETriggerEvent::Completed,
				this,
				&AAHPlayerCharacter::OnSlot3
			);
		}
		if (PC->Slot4Action)
		{
			EIC->BindAction(
				PC->Slot4Action,
				ETriggerEvent::Completed,
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
		if (PC->ReloadAction)
		{
			EIC->BindAction(
				PC->ReloadAction,
				ETriggerEvent::Completed,
				this,
				&AAHPlayerCharacter::OnReload
			);
		}
	}
	
}

void AAHPlayerCharacter::Move(const FInputActionValue& Value)
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

//get damage 있던 곳;;;

void AAHPlayerCharacter::HandleDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Death"));
	Destroy();
}

void AAHPlayerCharacter::OnPrimeAction()
{
	if (CombatComp) CombatComp->ProcessPrimaryAction();
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
	if (MainWidget)
	{
		MainWidget->UpdateAmmoDisplay(CurrentAmmo, SpareAmmo);
	}
}

void AAHPlayerCharacter::UpdateCrosshairVisibility(bool bIsWeaponEquipped)
{
	if (MainWidget)
	{
		MainWidget->SetCrosshairVisibility(bIsWeaponEquipped);
	}
}

void AAHPlayerCharacter::ShowGameMessage(FString Message, bool bShow)
{
	if (MainWidget)
	{
		MainWidget->DisplayNotice(Message, bShow);
	}
}

void AAHPlayerCharacter::UpdateVisualState()
{
	if (PostProcessHandler && StatusComp)
	{
		float HPPercent = StatusComp->CurrentHP / StatusComp->MaxHP;
		PostProcessHandler->UpdateHealthVignette(HPPercent); // 
	}
}