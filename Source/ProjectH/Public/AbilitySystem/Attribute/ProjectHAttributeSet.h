// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "ProjectHAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class PROJECTH_API UProjectHAttributeSet : public UAttributeSet
{
    GENERATED_BODY()

public:
    UProjectHAttributeSet();

    // ====================
    // 기본 체력 관련
    // ====================
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UProjectHAttributeSet, Health)

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(UProjectHAttributeSet, MaxHealth)

    // ====================
    // 공격력/주문력
    // ====================
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    FGameplayAttributeData AttackPower;
    ATTRIBUTE_ACCESSORS(UProjectHAttributeSet, AttackPower)

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    FGameplayAttributeData SpellPower;
    ATTRIBUTE_ACCESSORS(UProjectHAttributeSet, SpellPower)

    // ====================
    // 크리티컬 관련
    // ====================
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    FGameplayAttributeData CritRate;
    ATTRIBUTE_ACCESSORS(UProjectHAttributeSet, CritRate)

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    FGameplayAttributeData CritDamage;
    ATTRIBUTE_ACCESSORS(UProjectHAttributeSet, CritDamage)

    // ====================
    // 쿨타임 관련
    // ====================
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    FGameplayAttributeData CooldownReduction;
    ATTRIBUTE_ACCESSORS(UProjectHAttributeSet, CooldownReduction)

    // ====================
    // 방어/데미지 감소
    // ====================
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    FGameplayAttributeData Defense;
    ATTRIBUTE_ACCESSORS(UProjectHAttributeSet, Defense)

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    FGameplayAttributeData DamageReduction;
    ATTRIBUTE_ACCESSORS(UProjectHAttributeSet, DamageReduction)

    // ====================
    // 이동/공격 속도
    // ====================
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    FGameplayAttributeData MoveSpeed;
    ATTRIBUTE_ACCESSORS(UProjectHAttributeSet, MoveSpeed)

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    FGameplayAttributeData AttackSpeed;
    ATTRIBUTE_ACCESSORS(UProjectHAttributeSet, AttackSpeed)
};