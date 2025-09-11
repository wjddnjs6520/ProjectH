// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ProjectHCharacterBase.h"
#include "InputActionValue.h"
#include "ProjectHPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTH_API AProjectHPlayerCharacter : public AProjectHCharacterBase
{
	GENERATED_BODY()
public:
	AProjectHPlayerCharacter();

protected:

	/** 카메라와 캐릭터 사이 거리/각도 담당 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* SpringArmComp;

	/** 실제 시점을 담당하는 카메라 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* CameraComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void PossessedBy(AController* NewController) override;

	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	void AbilityInput(const FInputActionValue& Value, FGameplayTag InputTag);

	void RotateToMouseCursor();

	
};
