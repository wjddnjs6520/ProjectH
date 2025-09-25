// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UBoxComponent;
class USceneComponent;
class UProjectileMovementComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UGameplayEffect;


UCLASS()
class PROJECTH_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectileBase();

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void InitialSetting(
		const FVector& CollisionSize,
		bool bFireImmediately,
		const FVector& ShootDir,
		float LifeTime = 5.f,
		bool bPenetrate = false,
		float MaxSpeed = 2000.f,
		float InitSpeed = 1500.f
	);

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void DamageSetting(const float Damagemutiple);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* RootSceneComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effects")
	UNiagaraComponent* TrailVFX;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UNiagaraSystem* ImpactVFX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect")
	TSubclassOf<UGameplayEffect> ProjectileHitEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect")
	TSubclassOf<UGameplayEffect> ProjectileDamageEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	bool bCanPenetrate = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	bool bFiretile = false;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void FireInDirection(const FVector& ShootDir);

	UFUNCTION()
	void DisableCollisionAfterDelay(float DelayTime = 0.2f);

	/** 계수 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float AbilityDamagemutiple = 1.f;
};
