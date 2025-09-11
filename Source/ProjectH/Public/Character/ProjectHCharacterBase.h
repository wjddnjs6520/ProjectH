// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Character/CharacterDataAsset.h"
#include "ProjectHCharacterBase.generated.h"

class UProjectHAttributeSet;
class UProjectHAbilitySystemComponent;

UCLASS()
class PROJECTH_API AProjectHCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AProjectHCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

	/** Ability System Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	UAbilitySystemComponent* AbilitySystemComponent;

	/** Attribute Set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	UProjectHAttributeSet* AttributeSet;

	/** IAbilitySystemInterface 구현 */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable)
	void InitialSetting();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Data")
	UCharacterDataAsset* CharacterData;
};
