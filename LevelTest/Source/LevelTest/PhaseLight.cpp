#include "PhaseLight.h"
#include "Components/PointLightComponent.h"
#include "HorrorGameMode.h"
#include "Kismet/GameplayStatics.h"

APhaseLight::APhaseLight()
{
	PrimaryActorTick.bCanEverTick = false;

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	RootComponent = PointLight;
	DefaultIntensity = 5000.f;
	PointLight->SetIntensity(DefaultIntensity);
}

// Called when the game starts or when spawned
void APhaseLight::BeginPlay()
{
	Super::BeginPlay();

	// GameMode의 2차 방송국에 주파수를 맞춥니다.
	if (AHorrorGameMode* GM = Cast<AHorrorGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		GM->OnGlobalPhaseChanged.AddUObject(this, &APhaseLight::OnPhaseChanged);
	}
}

void APhaseLight::OnPhaseChanged(int32 NewPhase)
{
	// 페이즈 숫자에 따른 공포 단계 조절
	switch (NewPhase)
	{
	case 1:
		PointLight->SetIntensity(DefaultIntensity * 0.6f);
		break;

	case 2: 
		PointLight->SetLightColor(FColor(255, 230, 150));
		break;

	case 3:
		PointLight->SetLightColor(FColor::Red);
		GetWorldTimerManager().SetTimer(FlickerTimerHandle, this, &APhaseLight::ToggleFlicker, FlickerInterval, true);
		break;

	case 4:
		FlickerInterval = 0.05f;
		PointLight->SetIntensity(DefaultIntensity * 0.3f);
		break;
	}
}

void APhaseLight::ToggleFlicker()
{
	PointLight->SetVisibility(!PointLight->IsVisible());
}