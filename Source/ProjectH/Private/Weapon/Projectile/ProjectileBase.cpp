// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Projectile/ProjectileBase.h"

#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

#include "GameplayEffect.h"
#include "AbilitySystem/ProjectHAbilitySystemComponent.h"

#include "Character/ProjectHEnemyBase.h"
#include "ProjectHTags.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;

    RootSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
    RootComponent = RootSceneComp;

    CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
    CollisionComp->InitBoxExtent(FVector(10.f, 10.f, 10.f));
    CollisionComp->SetCollisionProfileName("Projectile");
    CollisionComp->SetupAttachment(RootSceneComp);

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->InitialSpeed = 2000.f;
    ProjectileMovement->MaxSpeed = 2000.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->ProjectileGravityScale = 0.f;

    TrailVFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("TrailVFX"));
    TrailVFX->SetupAttachment(RootSceneComp);
    TrailVFX->bAutoActivate = true;
}

void AProjectileBase::InitialSetting(
    const FVector& CollisionSize, 
    bool bFireImmediately, 
    const FVector& ShootDir, 
    float LifeTime, 
    bool bPenetrate, 
    const float MaxSpeed, 
    const float InitSpeed)
{
    if (UBoxComponent* Box = Cast<UBoxComponent>(CollisionComp))
    {
        Box->SetBoxExtent(CollisionSize);
    }

    if (LifeTime > 0.f)
    {
        SetLifeSpan(LifeTime);
    }

    bCanPenetrate = bPenetrate;
    bFiretile = bFireImmediately;

    ProjectileMovement->MaxSpeed = MaxSpeed;
    ProjectileMovement->InitialSpeed = InitSpeed;

    FireInDirection(ShootDir);
}

void AProjectileBase::DamageSetting(const float Damagemutiple)
{
    AbilityDamagemutiple = Damagemutiple;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

    if (CollisionComp)
    {
        CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::OnOverlapBegin);
    }

    if (TrailVFX)
    {
        TrailVFX->Activate(true); // true로 하면 이미 Spawn 시 작동
    }
}

void AProjectileBase::OnOverlapBegin(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (!OtherActor || OtherActor == this) return;

    AProjectHEnemyBase* Enemy = Cast<AProjectHEnemyBase>(OtherActor);
    if (!Enemy) return;

    UAbilitySystemComponent* EnemyASC = Enemy->GetAbilitySystemComponent();
    if (!EnemyASC) return;

    FGameplayEffectContextHandle EffectContext = EnemyASC->MakeEffectContext();
    EffectContext.AddInstigator(GetOwner(), Cast<APawn>(GetOwner()));

    //
    if (ProjectileHitEffect)
    {
        FGameplayEffectSpecHandle HitSpec = EnemyASC->MakeOutgoingSpec(ProjectileHitEffect, 1.f, EffectContext);
        if (HitSpec.IsValid())
        {
            EnemyASC->ApplyGameplayEffectSpecToSelf(*HitSpec.Data.Get());
        }
    }

    //
    if (ProjectileDamageEffect)
    {
        FGameplayEffectSpecHandle DamageSpec = EnemyASC->MakeOutgoingSpec(ProjectileDamageEffect, 1.f, EffectContext);
        if (DamageSpec.IsValid() && DamageSpec.Data.IsValid())
        {
            DamageSpec.Data->SetSetByCallerMagnitude(Data_Damagemultiple, AbilityDamagemutiple);
            EnemyASC->ApplyGameplayEffectSpecToSelf(*DamageSpec.Data.Get());
        }
    }

    // 발사체 처리
    if (bFiretile)
    {
        if (!bCanPenetrate) Destroy();
    }
    else
    {
        DisableCollisionAfterDelay(0.2f);
    }
}

void AProjectileBase::FireInDirection(const FVector& ShootDir)
{
    if (ProjectileMovement)
    {
        ProjectileMovement->Velocity = ShootDir.GetSafeNormal() * ProjectileMovement->InitialSpeed;
    }
}

void AProjectileBase::DisableCollisionAfterDelay(float DelayTime)
{
    if (!CollisionComp) return;

    FTimerHandle TimerHandle;
    GetWorldTimerManager().SetTimer(
        TimerHandle,
        [this]()
        {
            if (CollisionComp)
            {
                CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            }
        },
        DelayTime,
        false
    );
}
