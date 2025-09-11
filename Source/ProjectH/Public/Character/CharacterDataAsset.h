// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AbilitySystem/Ability/ProjectHGameplayAbility.h"
#include "AbilitySystem/Attribute/ProjectHAttributeSet.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "CharacterDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTH_API UCharacterDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
    /** 캐릭터 기본 부여 Ability 목록 (GA 사용용) */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS|Abilities")
    TArray<TSubclassOf<UProjectHGameplayAbility>> DefaultAbilities;

    /** 캐릭터 기본 AttributeSet 클래스 */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS|Attributes")
    TSubclassOf<UProjectHAttributeSet> AttributeSetClass;

    /** GA용 입력 태그 → InputAction 매핑 */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS|Input")
    TMap<FGameplayTag, TObjectPtr<UInputAction>> AbilityInputTagMapping;

    /** 캐릭터 전용 IMC */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    TObjectPtr<UInputMappingContext> DefaultIMC;

    /** 일반 이동/마우스 회전 InputAction */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    TObjectPtr<UInputAction> MoveAction;
};
