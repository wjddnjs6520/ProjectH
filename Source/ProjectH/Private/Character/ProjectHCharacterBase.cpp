// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ProjectHCharacterBase.h"

// Sets default values
AProjectHCharacterBase::AProjectHCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AProjectHCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectHCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AProjectHCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

