// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/ProjectHGameplayAbility.h"
#include "DefaultAttackAbility.generated.h"

class AProjectileBase;
/**
 * 
 */
UCLASS()
class PROJECTH_API UDefaultAttackAbility : public UProjectHGameplayAbility
{
	GENERATED_BODY()

public:
    UDefaultAttackAbility();

    virtual void ActivateAbility(
        const FGameplayAbilitySpecHandle Handle,
        const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo,
        const FGameplayEventData* TriggerEventData
    ) override;

    virtual void EndAbility(
        const FGameplayAbilitySpecHandle Handle,
        const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo,
        bool bReplicateEndAbility,
        bool bWasCancelled
    ) override;

protected:
    /** 발사할 Projectile 클래스 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
    TSubclassOf<AProjectileBase> ProjectileClass;

    /** 콜리전 크기 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
    FVector CollisionSize = FVector(10.f, 10.f, 10.f);

    /** 발사체 수명 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
    float ProjectileLifeTime = 5.f;

    /** 관통 여부 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
    bool bCanPenetrate = false;

    /** 초기 발사 여부 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
    bool bFireImmediately = true;

    /** 초기 발사 방향 (보통 캐릭터 전방) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
    FVector InitialShootDirection = FVector::ForwardVector;

};
