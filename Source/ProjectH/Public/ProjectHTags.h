// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"


//Ability Tag
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Player_Dash);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Player_DefaultAttack);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Enemy_ReactHit);

//Stat Tag
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stat_Player_Immune);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stat_Player_Ready_DefaultAttack);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stat_Enemy_ReactHit);


//Cooldown Tag
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Cooldown_Ability_Dash);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Cooldown_Ability_DefaultAttack);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Cooldown_ReactHit);


//Data Tag
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Data_Cooldown);

//Cue Tag
UE_DECLARE_GAMEPLAY_TAG_EXTERN(GamePlayCue_Ability_Player_DefaultAttack);