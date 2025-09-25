// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/ProjectHGameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/Attribute/ProjectHAttributeSet.h"
#include "ProjectHTags.h"

bool UProjectHGameplayAbility::ApplyCooldownGE()
{
    UAbilitySystemComponent* ASC = CurrentActorInfo->AbilitySystemComponent.Get();
    if (!ASC || !CooldownGameplayEffect) return false;

    float CooldownReduction = 0.f;
    if (const UProjectHAttributeSet* AttrSet = ASC->GetSet<UProjectHAttributeSet>())
    {
        CooldownReduction = AttrSet->GetCooldownReduction();
    }

    float ModifiedCooldown = BaseCooldown * (1.f - CooldownReduction);

    // SpecHandle 생성
    FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(CooldownGameplayEffect, GetAbilityLevel(), ASC->MakeEffectContext());
    if (SpecHandle.IsValid() && SpecHandle.Data.IsValid())
    {
        // Duration을 SetByCaller 값으로 전달
        SpecHandle.Data->SetSetByCallerMagnitude(Data_Cooldown, ModifiedCooldown);

        // GE 적용
        ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

        UE_LOG(LogTemp, Warning, TEXT("[Cooldown] Applied: %f sec"), ModifiedCooldown);
        return true;
    }

    return false;
}

