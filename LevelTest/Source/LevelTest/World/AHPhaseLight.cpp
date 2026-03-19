#include "AHPhaseLight.h"
#include "Components/PointLightComponent.h"
#include "Game/AHGameMode.h"
#include "Kismet/GameplayStatics.h"

AAHPhaseLight::AAHPhaseLight()
{
	PrimaryActorTick.bCanEverTick = false;

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	RootComponent = PointLight;
	DefaultIntensity = 5000.f;
	PointLight->SetIntensity(DefaultIntensity);
}

// Called when the game starts or when spawned
void AAHPhaseLight::BeginPlay()
{
	Super::BeginPlay();

	// GameMode의 2차 방송국에 주파수를 맞춥니다.
	if (AAHGameMode* GM = Cast<AAHGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		GM->OnGlobalPhaseChanged.AddUObject(this, &AAHPhaseLight::OnPhaseChanged);
	}
}

void AAHPhaseLight::OnPhaseChanged(int32 NewPhase)
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
		GetWorldTimerManager().SetTimer(FlickerTimerHandle, this, &AAHPhaseLight::ToggleFlicker, FlickerInterval, true);
		break;

	case 4:
		FlickerInterval = 0.05f;
		PointLight->SetIntensity(DefaultIntensity * 0.3f);
		break;
	}
}

void AAHPhaseLight::ToggleFlicker()
{
	PointLight->SetVisibility(!PointLight->IsVisible());
}