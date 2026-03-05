#include "AHMainWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Materials/MaterialInstanceDynamic.h"

void UAHMainWidget::NativeTick(const FGeometry& MyGeometry, float DeltaSeconds)
{
	Super::NativeTick(MyGeometry, DeltaSeconds);

	if (CurrentSpread > 0.0f)
	{
		CurrentSpread = FMath::FInterpTo(CurrentSpread, 0.0f, DeltaSeconds, 10.0f);
		// 0.0으로 부드럽게 보간 (10.0f는 복구 속도입니다)
		if (CrosshairImage)
		{
			float FinalScale = 1.0f + CurrentSpread;
			CrosshairImage->SetRenderScale(FVector2D(FinalScale, FinalScale));
		}
	}
}

void UAHMainWidget::SetCrosshairVisibility(bool visible)
{
	ESlateVisibility NewVisibility = visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	if (CrosshairImage)
	{
		CrosshairImage->SetVisibility(NewVisibility);
	}
	if (WeaponImage)
	{
		WeaponImage->SetVisibility(NewVisibility);
	}if (CurrentAmmoText)
	{
		CurrentAmmoText->SetVisibility(NewVisibility);
	}
	if (SpareAmmoText)
	{
		SpareAmmoText->SetVisibility(NewVisibility);
	}
}

void UAHMainWidget::UpadateHeartRate(float HeartPercent)
{
	if (HeartRateImage)
	{
		UMaterialInstanceDynamic* DynamicMat = HeartRateImage->GetDynamicMaterial();
		if (DynamicMat)
		{
			DynamicMat->SetScalarParameterValue(FName("HealthPercent"), HeartPercent);

			float PulseSpeed = FMath::Lerp(5.0f, 1.0f, HeartPercent);
			DynamicMat->SetScalarParameterValue(FName("HRM_Speed"), PulseSpeed);
		}
	}
}

void UAHMainWidget::UpdateCrosshairSpread(float SpreadAmount)
{
	if (CrosshairImage)

	{
		CurrentSpread = SpreadAmount;
		float NewScale = 1.0f + SpreadAmount;
		CrosshairImage->SetRenderScale(FVector2D(NewScale, NewScale));
	}
}

void UAHMainWidget::UpdateAmmoDisplay(int32 CurrentAmmo, int32 SpareAmmo)
{
	if (CurrentAmmoText)
		CurrentAmmoText->SetText(FText::AsNumber(CurrentAmmo));

	if (SpareAmmoText)
		SpareAmmoText->SetText(FText::AsNumber(SpareAmmo));
}

void UAHMainWidget::DisplayNotice(const FString& Content, bool bIsvisible)
{
	if (NoteText)
	{
		NoteText->SetText(FText::FromString(Content));
		NoteText->SetVisibility(bIsvisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}
