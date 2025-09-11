// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ProjectHCharacterBase.h"
#include "AbilitySystem/Attribute/ProjectHAttributeSet.h"
#include "AbilitySystem/ProjectHAbilitySystemComponent.h"

// Sets default values
AProjectHCharacterBase::AProjectHCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	AbilitySystemComponent = CreateDefaultSubobject<UProjectHAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

}

// Called when the game starts or when spawned
void AProjectHCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectHCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitialSetting();
}

UAbilitySystemComponent* AProjectHCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AProjectHCharacterBase::InitialSetting()
{
	if (!AbilitySystemComponent || !CharacterData)
		return;

	if (CharacterData->AttributeSetClass)
	{
		AttributeSet = NewObject<UProjectHAttributeSet>(AbilitySystemComponent, CharacterData->AttributeSetClass);
		AbilitySystemComponent->AddAttributeSetSubobject(AttributeSet);
	}

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	for (auto &AbilityClass : CharacterData->DefaultAbilities)
	{
		if (AbilityClass)
		{
			FGameplayAbilitySpec AbilitySpec(AbilityClass, 1); // 레벨 1 기본
			AbilitySystemComponent->GiveAbility(AbilitySpec);
		}
	}
}

