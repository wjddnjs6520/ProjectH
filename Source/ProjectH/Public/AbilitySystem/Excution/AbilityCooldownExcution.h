// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "AbilityCooldownExcution.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTH_API UAbilityCooldownExcution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UAbilityCooldownExcution();

	virtual void Execute_Implementation(
		const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		FGameplayEffectCustomExecutionOutput& OutExecutionOutput
	) const override;
};
