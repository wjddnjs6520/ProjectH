// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/DefaultAttackAbility.h"

UDefaultAttackAbility::UDefaultAttackAbility()
{
}

void UDefaultAttackAbility::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, 
	const FGameplayEventData* TriggerEventData
)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("AutoAttack Executed!"));

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UDefaultAttackAbility::EndAbility(
	const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, 
	bool bReplicateEndAbility, 
	bool bWasCancelled
)
{
	UE_LOG(LogTemp, Log, TEXT("AutoAttack End!"));

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
