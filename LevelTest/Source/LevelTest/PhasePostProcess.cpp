#include "PhasePostProcess.h"
#include "Components/PostProcessComponent.h"
#include "HorrorGameMode.h"
#include "Kismet/GameplayStatics.h"

APhasePostProcess::APhasePostProcess()
{
	PrimaryActorTick.bCanEverTick = false;
	PostProcessComp = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcessComp"));
	PostProcessComp->bUnbound = true; //레벨 전체 적용
	FPostProcessSettings& Settings = PostProcessComp->Settings;
    PostProcessComp->Priority = 10000.f;
	Settings.bOverride_AmbientOcclusionIntensity = true;
	Settings.AmbientOcclusionIntensity = 1.0f;


}

void APhasePostProcess::BeginPlay()
{
	Super::BeginPlay();
	
	if (AHorrorGameMode* GM = Cast<AHorrorGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		GM->OnGlobalPhaseChanged.AddUObject(this, &APhasePostProcess::UpdatePostProcess);
	}
}


void APhasePostProcess::UpdatePostProcess(int32 NewPhase)
{
    if (!PostProcessComp) return;
    FPostProcessSettings& Settings = PostProcessComp->Settings;

    switch (NewPhase)
    {
    case 1:
        CurrentPhaseVignette = 0.6f;
        Settings.bOverride_FilmGrainIntensity = true;
        Settings.FilmGrainIntensity = 0.2f;
        break;

    case 2:
        CurrentPhaseVignette = 0.8f;
        break;

    case 3:
        CurrentPhaseVignette = 1.0f;
        Settings.bOverride_ColorSaturation = true;
        Settings.ColorSaturation = FVector4(0.5f, 0.5f, 0.5f, 1.0f);
        break;

    case 4:
        // 최종 단계: 색수차(SceneFringe), 강한 노이즈, 극도의 시야 제한
        CurrentPhaseVignette = 1.2f;
        Settings.bOverride_SceneFringeIntensity = true;
        Settings.SceneFringeIntensity = 5.0f; // 화면 번짐 효과
        Settings.bOverride_FilmGrainIntensity = true;
        Settings.FilmGrainIntensity = 1.0f;
        break;
    }

    // [핵심] 모든 페이즈에서 계산된 최종 비네트 수치를 적용합니다.
    Settings.bOverride_VignetteIntensity = true;
    Settings.VignetteIntensity = CurrentPhaseVignette;
}

void APhasePostProcess::UpdateHealthVignette(float HPPercent)
{
	float HealthPenalty = (1.0f - HPPercent) * 15.f; // 테스트용 
	PostProcessComp->Settings.VignetteIntensity = CurrentPhaseVignette + HealthPenalty;
    UE_LOG(LogTemp, Warning, TEXT("Case1 %f"), CurrentPhaseVignette + HealthPenalty);
}
