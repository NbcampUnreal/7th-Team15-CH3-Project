#include "Actors/EventActors/READABLE.h"
#include "Characters/Controller/AHPlayerController.h"
#include "Characters/Player/AHPlayerCharacter.h"
#include "Subsystem/EventSubsystem.h"

void AREADABLE::Interact(AActor* Interactor)
{
    AAHPlayerCharacter* Player = Cast<AAHPlayerCharacter>(Interactor);
    
    AAHPlayerController* PC = Cast<AAHPlayerController>(Player->GetController());
    if (!Player) return;

    if (!bIsReading)
    {
        UEventSubsystem* EventSubsystem = GetGameInstance()->GetSubsystem<UEventSubsystem>();
        if (EventSubsystem)
        {
            // 1. 이벤트 서브시스템을 통해 메시지 발송
            EventSubsystem->OnDisplay.Broadcast(NoteMessage, bIsReading);
            // FString, Content, bool, bIsvisible
            // 2. 입력 제한 등 필요한 상태 처리
            Player->DisableInput(Cast<APlayerController>(Player->GetController()));
            bIsReading = true;
        }
    }
    else
    {
        //Player->ShowGameMessage("", false);
        Player->EnableInput(Cast<APlayerController>(Player->GetController()));
        bIsReading = false;

        OnNoteReadFinished.Broadcast(this);
        
        Player->EnableInput(Cast<APlayerController>(Player->GetController()));

        Destroy();
        // E 재입력으로 닫기, 문서하나당 DELEGATE 한번쓰기
    }
}
