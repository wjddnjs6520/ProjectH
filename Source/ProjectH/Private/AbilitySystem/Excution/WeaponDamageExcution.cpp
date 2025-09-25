// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Excution/WeaponDamageExcution.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "GameplayTagContainer.h"
#include "GameplayEffect.h"
#include "AbilitySystem/Attribute/ProjectHAttributeSet.h"
#include "ProjectHTags.h"

UWeaponDamageExcution::UWeaponDamageExcution()
{
}


void UWeaponDamageExcution::Execute_Implementation(
    const FGameplayEffectCustomExecutionParameters& ExecutionParams,
    FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
    // -------------------------------
    // 1. 시전자, 타겟 ASC 가져오기
    // -------------------------------
    UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
    UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

    if (!SourceASC || !TargetASC) return;

    // -------------------------------
    // 2. SetByCaller로 전달된 계수 가져오기
    // -------------------------------
    float DamageMultiplier = Spec.GetSetByCallerMagnitude(Data_Damagemultiple, false);

    // -------------------------------
    // 3. 시전자 공격력 가져오기
    // -------------------------------
    float AttackPower = 0.f;
    if (const UProjectHAttributeSet* SourceAttrSet = SourceASC->GetSet<UProjectHAttributeSet>())
    {
        AttackPower = SourceAttrSet->GetAttackPower();
    }

    // -------------------------------
    // 4. 기본 데미지 계산
    // -------------------------------
    float FinalDamage = AttackPower * DamageMultiplier;

    // -------------------------------
    // 5. 크리티컬 체크
    // -------------------------------
    float CritRate = 0.f;
    float CritDamage = 1.f;
    if (const UProjectHAttributeSet* SourceAttrSet = SourceASC->GetSet<UProjectHAttributeSet>())
    {
        CritRate = SourceAttrSet->GetCritRate();
        CritDamage = SourceAttrSet->GetCritDamage();
    }

    if (FMath::FRand() <= CritRate)
    {
        FinalDamage *= CritDamage; // 크리티컬 데미지 적용
    }

    // -------------------------------
    // 6. 타겟 방어력/피해감소 적용
    // -------------------------------
    float TargetDefense = 0.f;
    float TargetDamageReduction = 0.f;
    if (const UProjectHAttributeSet* TargetAttrSet = TargetASC->GetSet<UProjectHAttributeSet>())
    {
        TargetDefense = TargetAttrSet->GetDefense();
        TargetDamageReduction = TargetAttrSet->GetDamageReduction();
    }

    FinalDamage = FMath::Max(0.f, FinalDamage - TargetDefense); // 방어력 차감
    FinalDamage *= (1.f - TargetDamageReduction); // 피해감소 적용

    // -------------------------------
    // 7. HP에 적용
    // -------------------------------
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(
        FGameplayAttribute(UProjectHAttributeSet::GetHealthAttribute()),
        EGameplayModOp::Additive,
        -FinalDamage
    ));

    UE_LOG(LogTemp, Log, TEXT("TakeDamage: Applied %f damage to target"), FinalDamage);
}
