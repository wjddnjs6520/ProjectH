// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "WeaponDamageExcution.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTH_API UWeaponDamageExcution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
    UWeaponDamageExcution();

    /** 실제 데미지 계산 및 출력 */
    virtual void Execute_Implementation(
        const FGameplayEffectCustomExecutionParameters& ExecutionParams,
        FGameplayEffectCustomExecutionOutput& OutExecutionOutput
    ) const override;
};
