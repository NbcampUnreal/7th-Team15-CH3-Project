#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AHHUD.generated.h"

class UAHMainWidget;

UCLASS()
class LEVELTEST_API AAHHUD : public AHUD
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UAHMainWidget> MainHUDWidgetClass;

    UPROPERTY()
    UAHMainWidget* MainHUDWidget;

    UFUNCTION(BlueprintCallable, Category = "UI")
    UAHMainWidget* GetMainWidget() const { return MainHUDWidget; }

protected:
    virtual void BeginPlay() override;
};