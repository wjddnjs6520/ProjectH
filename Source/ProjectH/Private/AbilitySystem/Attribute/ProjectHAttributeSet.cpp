// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attribute/ProjectHAttributeSet.h"

UProjectHAttributeSet::UProjectHAttributeSet()
{
    InitHealth(100.f);
    InitMaxHealth(100.f);
    InitAttackPower(10.f);
    InitSpellPower(10.f);
    InitCritRate(5.f);
    InitCritDamage(150.f);
    InitCooldownReduction(0.0f);
    InitDefense(0.f);
    InitDamageReduction(0.f);
    InitMoveSpeed(600.f);
    InitAttackSpeed(1.f);
}
