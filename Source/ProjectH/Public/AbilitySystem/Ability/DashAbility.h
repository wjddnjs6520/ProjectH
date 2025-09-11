// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/ProjectHGameplayAbility.h"
#include "DashAbility.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTH_API UDashAbility : public UProjectHGameplayAbility
{
	GENERATED_BODY()

public:
    UDashAbility();

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
    UPROPERTY(EditDefaultsOnly, Category = "Dash")
    float DashDistance = 600.f;

    UPROPERTY(EditDefaultsOnly, Category = "Dash")
    float DashDuration = 0.3f;

private:
    FVector StartLocation;
    FVector TargetLocation;
    float ElapsedTime;
    FTimerHandle DashTimerHandle;
};
