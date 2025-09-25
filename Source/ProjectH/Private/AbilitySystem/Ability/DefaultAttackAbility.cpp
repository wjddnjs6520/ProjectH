// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/DefaultAttackAbility.h"

#include "AbilitySystem/ProjectHAbilitySystemComponent.h"

#include "Weapon/Projectile/ProjectileBase.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

UDefaultAttackAbility::UDefaultAttackAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UDefaultAttackAbility::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, 
	const FGameplayEventData* TriggerEventData
)
{
	if (!ApplyCooldownGE())
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	if (!ProjectileClass || !ActorInfo || !ActorInfo->AvatarActor.IsValid())
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	UWorld* World = ActorInfo->AvatarActor->GetWorld();
	if (!World)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	FVector SpawnLocation = FVector::ZeroVector;
	FRotator SpawnRotation = FRotator::ZeroRotator;

	if (ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get()))
	{
		if (USkeletalMeshComponent* Mesh = Character->GetMesh())
		{
			FVector Forward = Mesh->GetForwardVector();
			FVector Right = Mesh->GetRightVector(); // 캐릭터 기준 오른쪽 벡터

			// 캐릭터 전방 100 + 오른쪽 100 + 높이 50
			SpawnLocation = ActorInfo->AvatarActor->GetActorLocation()
				+ Right * 50
				+ FVector(0.f, 0.f, 50.f);

			SpawnRotation = Mesh->GetForwardVector().Rotation();
			SpawnRotation.Yaw -= 135.f;
		}
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = ActorInfo->AvatarActor.Get();
	SpawnParams.Instigator = Cast<APawn>(ActorInfo->AvatarActor.Get());
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	// Projectile 스폰
	if (AProjectileBase* Projectile = World->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams))
	{
		Projectile->InitialSetting(CollisionSize, bFireImmediately, InitialShootDirection, ProjectileLifeTime, bCanPenetrate);
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
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
