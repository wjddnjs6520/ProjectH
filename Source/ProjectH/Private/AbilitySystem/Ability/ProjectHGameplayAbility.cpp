// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/ProjectHGameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/Attribute/ProjectHAttributeSet.h"
#include "ProjectHTags.h"


void UProjectHGameplayAbility::ApplyCooldown(
    const FGameplayAbilitySpecHandle Handle, 
    const FGameplayAbilityActorInfo* ActorInfo, 
    const FGameplayAbilityActivationInfo ActivationInfo) const
{
    if (!ActorInfo) return;

    UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
    UGameplayEffect* CooldownGE = GetCooldownGameplayEffect();
    if (!ASC || !CooldownGE) return;

    float CooldownReduction = 0.f;
    if (const UProjectHAttributeSet* AttrSet = ASC->GetSet<UProjectHAttributeSet>())
    {
        CooldownReduction = FMath::Clamp(AttrSet->GetCooldownReduction(), 0.f, 0.95f);
    }

    float ModifiedCooldown = BaseCooldown * (1.f - CooldownReduction);

    // SpecHandle 생성
    FGameplayEffectSpecHandle CooldownSpec = ASC->MakeOutgoingSpec(
        CooldownGE->GetClass(),
        GetAbilityLevel(Handle, ActorInfo),
        ASC->MakeEffectContext()
    );

    if (CooldownSpec.IsValid() && CooldownSpec.Data.IsValid())
    {
        // SetByCaller로 Duration 전달
        CooldownSpec.Data->SetSetByCallerMagnitude(Data_Cooldown, ModifiedCooldown);

        UE_LOG(LogTemp, Warning, TEXT("[ApplyCooldown] Prepared SetByCaller Duration: %f"), ModifiedCooldown);
        ASC->ApplyGameplayEffectSpecToSelf(*CooldownSpec.Data.Get());
    }
}
