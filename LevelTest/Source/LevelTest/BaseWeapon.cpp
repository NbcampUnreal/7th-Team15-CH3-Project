#include "BaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "CombatComponent.h"
#include "CombatInterface.h"
#include "GameFramework/Character.h"

ABaseWeapon::ABaseWeapon()
{
    PrimaryActorTick.bCanEverTick = false;

    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
    RootComponent = StaticMeshComp;

    StaticMeshComp->SetCollisionResponseToAllChannels(ECR_Block);
    StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
    WeaponMesh->SetupAttachment(RootComponent);

    WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABaseWeapon::Fire(const FVector& ShootLocation, const FRotator& ShootingRotation)
{
    FVector Start = ShootLocation;
    FVector ForwardVector = ShootingRotation.Vector();
    FVector End = Start + (ForwardVector * FireRange);

    FHitResult HitResult;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this); // 무기 자신 무시
    Params.AddIgnoredActor(GetOwner()); // 무기를 들고 있는 캐릭터 무시

    if (FireSound)//사운드 있으면 재생!
    {
        UGameplayStatics::PlaySoundAtLocation(this, FireSound, Start);
    }
    if (MuzzleFlash) //이펙트 있으면 재생
    {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlash, Start, ShootingRotation);
    }
    if (FireMontage) //발사 애니메이션
    {
        // 무기의 소유자(Character)를 찾아 몽타주 재생
        if (ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner()))
        {
            OwnerCharacter->PlayAnimMontage(FireMontage);
        }
    }

    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult,
        Start,
        End,
        ECollisionChannel::ECC_GameTraceChannel1, // 전투용 콜리전 채널 (Bullet 등)
        Params
    );

    if (bDrawDebugLine)
    {
        DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f, 0, 1.0f);
    }//디버그 라인

    if (bHit)//맞음,
    {
        if (ImpactEffect)
        {
            UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());
        }//탄착군 이펙트 

        AActor* HitActor = HitResult.GetActor();
        if (HitActor)
        {
            ICombatInterface* CombatInterface = Cast<ICombatInterface>(HitActor);
            if (CombatInterface)
            {
                CombatInterface->GetDamage(BaseDamage);
                UE_LOG(LogTemp, Warning, TEXT("Hit Target: %s"), *HitActor->GetName());
            }
        }// 상대방 대미지 처리 (ICombatInterface 활용)
    }
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseWeapon::SecondaryAction(bool bIsPressed)
{
    if (bIsPressed)
    {
        UE_LOG(LogTemp, Warning, TEXT("Aiming Start!"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Aiming End!"));
    }
}

void ABaseWeapon::Interact(AActor* Interactor)
{
    if (Interactor)
    {
        UCombatComponent* CombatComp = Interactor->FindComponentByClass<UCombatComponent>();
        if (CombatComp)
        {
            CombatComp->AddWeaponToQuickbar(this->GetClass());

            this->Destroy(); // 무기 줍고 나(무기) 없애기
        }
    }
}

void ABaseWeapon::PlayEmptySound()
{
    if (EmptySound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, EmptySound, GetActorLocation());
    }
}