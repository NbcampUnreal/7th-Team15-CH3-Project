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
	
protected: 
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

	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaSeconds) override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* NoteText;

public:
	UFUNCTION(BlueprintCallable, Category ="UI")
	void SetCrosshairVisibility(bool visible);

	UFUNCTION(BlueprintCallable, Category ="UI")
	void UpadateHeartRate(float HeartPercent);

	UFUNCTION(BlueprintCallable, Category = "Samsara|UI")
	void UpdateCrosshairSpread(float SpreadAmount);

	void UpdateAmmoDisplay(int32 CurrentAmmo, int32 SpareAmmo);

	void DisplayNotice(const FString& Content, bool bIsvisible);

private:
	float CurrentSpread = 2.f;
};
