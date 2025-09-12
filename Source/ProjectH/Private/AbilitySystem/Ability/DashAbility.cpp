// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/Ability/DashAbility.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "AbilitySystem/ProjectHAbilitySystemComponent.h"
#include "ProjectHTags.h"
#include "Character/ProjectHPlayerController.h"
#include "Components/CapsuleComponent.h"

UDashAbility::UDashAbility()
{
}

void UDashAbility::ActivateAbility(
    const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData
)
{
    if (!ActorInfo || !ActorInfo->AvatarActor.IsValid()) return;
    ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
    if (!Character) return;

    UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
    if (!ASC) return;

    if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
        return;
    }

    // 1️⃣ Dash 태그 부여
    FGameplayTag DashTag = Stat_Player_Immune;
    ASC->AddLooseGameplayTag(DashTag);
    UE_LOG(LogTemp, Warning, TEXT("Dash Start: Immune Tag Added"));

    if (UCapsuleComponent* Capsule = Character->GetCapsuleComponent())
    {
        // 모든 채널 Block → Default, Pawn만 Ignore
        Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        Capsule->SetCollisionResponseToAllChannels(ECR_Block);
        Capsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
    }

    // 3️⃣ 이동 계산 (마우스 방향)
    AProjectHPlayerController* PC = Cast<AProjectHPlayerController>(Character->GetController());
    if (!PC) return;

    FVector MouseWorldPos, MouseWorldDir;
    if (!PC->DeprojectMousePositionToWorld(MouseWorldPos, MouseWorldDir)) return;

    FVector PlaneIntersect = FMath::LinePlaneIntersection(
        MouseWorldPos,
        MouseWorldPos + MouseWorldDir * 10000.f,
        FVector(0.f, 0.f, Character->GetActorLocation().Z),
        FVector::UpVector
    );

    FVector DashDir = (PlaneIntersect - Character->GetActorLocation()).GetSafeNormal();

    StartLocation = Character->GetActorLocation();
    TargetLocation = StartLocation + DashDir * DashDistance;
    ElapsedTime = 0.f;

    // 4️⃣ Tick / Timer로 Lerp 이동
    FTimerDelegate TimerDel;
    TimerDel.BindLambda([this, Character]() {
        float Delta = Character->GetWorld()->GetDeltaSeconds();
        ElapsedTime += Delta;

        float Alpha = FMath::Clamp(ElapsedTime / DashDuration, 0.f, 1.f);
        FVector NewLoc = FMath::Lerp(StartLocation, TargetLocation, Alpha);
        Character->SetActorLocation(NewLoc, true);

        UE_LOG(LogTemp, Warning, TEXT("Dash Moving: Alpha=%f, Location=%s"), Alpha, *NewLoc.ToString());

        if (Alpha >= 1.f)
        {
            UE_LOG(LogTemp, Warning, TEXT("Dash End: Calling EndAbility"));
            EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
        }
        });

    Character->GetWorldTimerManager().SetTimer(DashTimerHandle, TimerDel, 0.01f, true);
}

void UDashAbility::EndAbility(
    FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    bool bReplicateEndAbility,
    bool bWasCancelled
)
{
    if (!ActorInfo || !ActorInfo->AvatarActor.IsValid()) return;
    ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
    if (!Character) return;

    UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
    if (ASC)
    {
        // Dash 태그 제거
        FGameplayTag DashTag = Stat_Player_Immune;
        ASC->RemoveLooseGameplayTag(DashTag);
        UE_LOG(LogTemp, Warning, TEXT("Dash End: Immune Tag Removed"));
    }

    if (UCapsuleComponent* Capsule = Character->GetCapsuleComponent())
    {
        Capsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
    }

    // Timer 정리
    Character->GetWorldTimerManager().ClearTimer(DashTimerHandle);

    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
