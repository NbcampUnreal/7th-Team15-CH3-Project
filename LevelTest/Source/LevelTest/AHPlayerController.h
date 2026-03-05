#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AHPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class APlayerCharacter;


UCLASS()
class LEVELTEST_API AAHPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:
	AAHPlayerController();

#pragma region Input

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* JumpAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Combat")
	UInputAction* PrimeAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Combat")
	UInputAction* SecondAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Quickbar")
	UInputAction* Slot1Action;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Quickbar")
	UInputAction* Slot2Action;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Quickbar")
	UInputAction* Slot3Action;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Quickbar")
	UInputAction* Slot4Action;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Quickbar")
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Reload")
	UInputAction* ReloadAction;

#pragma endregion
	virtual void BeginPlay() override;

};
