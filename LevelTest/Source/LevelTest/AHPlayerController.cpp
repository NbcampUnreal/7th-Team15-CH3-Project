#include "AHPlayerController.h"
#include"EnhancedInputSubsystems.h"
#include"EnhancedInputComponent.h"
#include"APlayerCharacter.h"
#include"Blueprint/UserWidget.h"

AAHPlayerController::AAHPlayerController() :
    InputMappingContext(nullptr),
    MoveAction(nullptr),
    LookAction(nullptr),
    JumpAction(nullptr),
    SprintAction(nullptr),
    PrimeAction(nullptr),
    SecondAction(nullptr),
    Slot1Action(nullptr), 
    Slot2Action(nullptr),
    Slot3Action(nullptr),
    Slot4Action(nullptr),
    InteractAction(nullptr),
    ReloadAction(nullptr)
{
}


void AAHPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            if (InputMappingContext)
            {
                Subsystem->AddMappingContext(InputMappingContext, 0);
            }
        }
    }
}



