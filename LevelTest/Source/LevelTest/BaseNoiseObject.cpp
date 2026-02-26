#include "BaseNoiseObject.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include"Perception/AISense_Hearing.h"

// Sets default values
ABaseNoiseObject::ABaseNoiseObject()
{
 	PrimaryActorTick.bCanEverTick = false;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComp;

	MeshComp->SetSimulatePhysics(true);
	MeshComp->SetNotifyRigidBodyCollision(true);
	MeshComp->SetCollisionProfileName(TEXT("PhysicsActor"));

	MeshComp->OnComponentHit.AddDynamic(this, &ABaseNoiseObject::OnHit);

	PitchMultiplier = 1.f;


}

// Called when the game starts or when spawned
void ABaseNoiseObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseNoiseObject::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	float ImpulseStrength = NormalImpulse.Size();
	// FVector인 NormalImpulse를 float로 벡터 크기 가져오기 
	float VariableVolume = FMath::Clamp(ImpulseStrength / 2000.f, 0.5f, 2.0f);
	//  임펄스 스트렝스 값을 2000f으로 나누고 해당 값을 0.5f 에서 2.0f 사이 값으로 조정 

	float CurrentTime = GetWorld()->GetTimeSeconds();

	if (CurrentTime - LastNoiseTime < NoiseCooldown) return;

	if (NormalImpulse.Size() > ImpulsetoMakeSound)
	{
		UAISense_Hearing::ReportNoiseEvent(GetWorld(), GetActorLocation(), 1.0f, this, 0.0f, FName("Noise"));
		// GetInstigator 는 소음을 낸 대상을 반환한다,
		// GetActorLocation 루트 컴포넌트의 위치 벡터를 반환한다고 한다,

		LastNoiseTime = CurrentTime;

		if (CollisionSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, CollisionSound, GetActorLocation(), VariableVolume, PitchMultiplier);

			UE_LOG(LogTemp, Warning, TEXT("Sound Check"));
		}
	}
}



