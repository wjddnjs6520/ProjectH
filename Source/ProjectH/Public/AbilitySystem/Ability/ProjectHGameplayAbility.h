// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayEffect.h"
#include "ProjectHGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTH_API UProjectHGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cooldown")
    TSubclassOf<UGameplayEffect> CooldownGameplayEffect;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cooldown")
    float BaseCooldown = 1.0f;

    // 이 어빌리티가 실행할 GameplayCue 태그
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
    FGameplayTag AttackVFXCue;


    // Ability Commit 시점에 쿨타임 적용
    bool ApplyCooldownGE();
};
