// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Excution/AbilityCooldownExcution.h"
#include "AbilitySystem/Attribute/ProjectHAttributeSet.h"

UAbilityCooldownExcution::UAbilityCooldownExcution()
{
}

void UAbilityCooldownExcution::Execute_Implementation(
    const FGameplayEffectCustomExecutionParameters& ExecutionParams,
    FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
    if (!TargetASC)
    {
        UE_LOG(LogTemp, Warning, TEXT("[CooldownExecution] TargetASC is null! Returning."));
        return;
    }

    const UProjectHAttributeSet* TargetAttributes = TargetASC->GetSet<UProjectHAttributeSet>();
    if (!TargetAttributes)
    {
        UE_LOG(LogTemp, Warning, TEXT("[CooldownExecution] TargetAttributes is null! Returning."));
        return;
    }

    float CooldownReduction = TargetAttributes->GetCooldownReduction();
    float BaseCooldown = 5.f; // 기본 쿨타임
    float ModifiedCooldown = BaseCooldown * (1.f - CooldownReduction);

    UE_LOG(LogTemp, Warning, TEXT("[CooldownExecution] Base: %f, Reduction: %f, Result: %f"),
        BaseCooldown, CooldownReduction, ModifiedCooldown);

    // SetByCaller 이름과 계산된 값으로 Modifier 추가
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(
        FGameplayAttribute(),       // Attribute 없음
        EGameplayModOp::Override,   // Duration 덮어쓰기
        ModifiedCooldown
    ));
}

