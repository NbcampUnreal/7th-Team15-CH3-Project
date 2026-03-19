#include "World/READABLE.h"
#include "Character/AHPlayerCharacter.h"

void AREADABLE::Interact(AActor* Interactor)
{
    AAHPlayerCharacter* Player = Cast<AAHPlayerCharacter>(Interactor);
    if (!Player) return;

    if (!bIsReading)
    {
        Player->ShowGameMessage(NoteMessage, true);
        // 텍스트용 UI위젯 호출(MainWidget이라 고민, 그냥 UI 하나 새로파고 띄우는게 나을지도)

        Player->DisableInput(Cast<APlayerController>(Player->GetController()));
        bIsReading = true;
        // 이동정지, 
    }
    else
    {
        Player->ShowGameMessage("", false);
        Player->EnableInput(Cast<APlayerController>(Player->GetController()));
        bIsReading = false;

        OnNoteReadFinished.Broadcast(this);
        
        Player->EnableInput(Cast<APlayerController>(Player->GetController()));

        Destroy();
        // E 재입력으로 닫기, 문서하나당 DELEGATE 한번쓰기
    }
}
