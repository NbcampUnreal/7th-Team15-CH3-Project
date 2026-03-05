#pragma once

#include "CoreMinimal.h"
#include "InteractInterface.h"
#include "GameFramework/Actor.h"
#include "READABLE.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNoteReadFinished, class AREADABLE*);

UCLASS()
class LEVELTEST_API AREADABLE : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	

	FOnNoteReadFinished OnNoteReadFinished;

	virtual void Interact(AActor* Interactor) override;

	UPROPERTY(EditAnywhere, Category = "Note Content")
	FString NoteMessage;

	bool bIsReading = false;
};
