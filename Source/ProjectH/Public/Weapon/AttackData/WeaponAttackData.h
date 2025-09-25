#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayEffect.h"
#include "AbilitySystem/Attribute/ProjectHAttributeSet.h"
#include "WeaponAttackData.generated.h"

USTRUCT(BlueprintType)
struct FWeaponAttackData
{
    GENERATED_BODY()

    // 무기 장착 시 사용할 공격 어빌리티
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
    TSubclassOf<UGameplayAbility> AttackAbility;

    // 무기 장착 시 적용되는 패시브 효과 목록
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Passive")
    TArray<TSubclassOf<UGameplayEffect>> PassiveEffects;
};
