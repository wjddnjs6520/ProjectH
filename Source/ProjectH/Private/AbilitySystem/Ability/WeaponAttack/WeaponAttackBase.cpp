// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/WeaponAttack/WeaponAttackBase.h"

#include "AbilitySystem/ProjectHAbilitySystemComponent.h"

#include "Weapon/Projectile/ProjectileBase.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

UWeaponAttackBase::UWeaponAttackBase()
{
}

void UWeaponAttackBase::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, 
	const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	SpawnProjectile();

	UE_LOG(LogTemp, Log, TEXT("AutoAttack Executed!"));

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UWeaponAttackBase::EndAbility(
	const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, 
	bool bReplicateEndAbility, 
	bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UWeaponAttackBase::SpawnProjectile()
{
	if (!ProjectileSettings.ProjectileClass)
	{
		return;
	}

	UWorld* World = CurrentActorInfo->AvatarActor->GetWorld();
	if (!World)
	{
		return;
	}

	FVector SpawnLocation = FVector::ZeroVector;
	FRotator SpawnRotation = FRotator::ZeroRotator;

	if (ACharacter* Character = Cast<ACharacter>(CurrentActorInfo->AvatarActor.Get()))
	{
		if (USkeletalMeshComponent* Mesh = Character->GetMesh())
		{
			FVector Forward = Mesh->GetForwardVector();
			FVector Right = Mesh->GetRightVector(); // 캐릭터 기준 오른쪽 벡터

			// 캐릭터 전방 100 + 오른쪽 100 + 높이 50
			SpawnLocation = CurrentActorInfo->AvatarActor->GetActorLocation()
				+ Right * 50
				+ FVector(0.f, 0.f, 50.f);

			SpawnRotation = Mesh->GetForwardVector().Rotation();
			SpawnRotation.Yaw -= 135.f;
		}
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = CurrentActorInfo->AvatarActor.Get();
	SpawnParams.Instigator = Cast<APawn>(CurrentActorInfo->AvatarActor.Get());
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// Projectile 스폰
	if (AProjectileBase* Projectile = World->SpawnActor<AProjectileBase>(ProjectileSettings.ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams))
	{
		Projectile->InitialSetting(
			ProjectileSettings.CollisionSize,
			ProjectileSettings.bFireImmediately,
			ProjectileSettings.InitialShootDirection,
			ProjectileSettings.ProjectileLifeTime,
			ProjectileSettings.bCanPenetrate,
			ProjectileSettings.ProjectileMaxSpeed,
			ProjectileSettings.ProjectileInitSpeed
		);
		Projectile->DamageSetting(Coefficient);
	}
}
