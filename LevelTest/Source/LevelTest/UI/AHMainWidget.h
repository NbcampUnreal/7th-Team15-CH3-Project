#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AHMainWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class LEVELTEST_API UAHMainWidget : public UUserWidget
{
	GENERATED_BODY()
    
public:
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetCrosshairVisibility(bool bVisible);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateHeartRate(float HeartPercent);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateCrosshairSpread(float SpreadAmount);
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateAmmoDisplay(int32 CurrentAmmo, int32 SpareAmmo);
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void DisplayNotice(FString Content, bool bIsVisible);

protected:
	virtual void NativeConstruct() override;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaSeconds) override;
	
	UPROPERTY(meta = (BindWidget))
	UImage* CrosshairImage;

	UPROPERTY(meta = (BindWidget))
	UImage* HeartRateImage;

	UPROPERTY(meta = (BindWidget))
	UImage* WeaponImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentAmmoText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SpareAmmoText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* NoteText;

private:
	float CurrentSpread = 2.f;
};