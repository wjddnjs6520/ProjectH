// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ProjectHPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystem/ProjectHAbilitySystemComponent.h"
#include "Character/ProjectHPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AProjectHPlayerCharacter::AProjectHPlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    bUseControllerRotationYaw = false; // Controller Yaw에 메쉬 회전 맞추지 않음
    GetCharacterMovement()->bOrientRotationToMovement = false; // 이동 방향으로 회전
    GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f); // 회전 속도

    // SpringArm 생성
    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArmComp->SetupAttachment(RootComponent);
    SpringArmComp->TargetArmLength = 900.0f;
    SpringArmComp->bUsePawnControlRotation = false;
    SpringArmComp->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));

    // 카메라 생성
    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
    CameraComp->bUsePawnControlRotation = false;
}

void AProjectHPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectHPlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    RotateToMouseCursor();
}

void AProjectHPlayerCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    if (APlayerController* PC = Cast<APlayerController>(NewController))
    {
        UE_LOG(LogTemp, Warning, TEXT("PossessedBy: %s"), *PC->GetName());

        if (CharacterData && CharacterData->DefaultIMC)
        {
            if (ULocalPlayer* LocalPlayer = PC->GetLocalPlayer())
            {
                if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
                {
                    Subsystem->AddMappingContext(CharacterData->DefaultIMC, 0);

                    UE_LOG(LogTemp, Warning, TEXT("Added MappingContext: %s"), *CharacterData->DefaultIMC->GetName());
                }
            }
        }
    }
}


void AProjectHPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (!CharacterData || !AbilitySystemComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("SetupPlayerInputComponent FAILED: CharacterData or AbilitySystemComponent is nullptr"));
        return;
    }

    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // GA Ability 바인딩
        for (auto& InputMapping : CharacterData->AbilityInputTagMapping)
        {
            EnhancedInput->BindAction(
                InputMapping.Value,
                ETriggerEvent::Triggered,
                this,
                &AProjectHPlayerCharacter::AbilityInput,
                InputMapping.Key
            );
        }

        if (CharacterData->MoveAction)
        {
            EnhancedInput->BindAction(
                CharacterData->MoveAction,
                ETriggerEvent::Triggered,
                this,
                &AProjectHPlayerCharacter::Move
            );
        }

    }
}


void AProjectHPlayerCharacter::Move(const FInputActionValue& Value)
{
    FVector2D Axis = Value.Get<FVector2D>();
    if (!Controller || Axis.IsNearlyZero()) return;

    // 캐릭터 기준 월드 이동
    FVector MoveDir = FVector(Axis.Y, Axis.X, 0.f);
    MoveDir.Normalize();

    AddMovementInput(MoveDir, 1.f);
}


void AProjectHPlayerCharacter::AbilityInput(const FInputActionValue& Value, FGameplayTag InputTag)
{
    if (!AbilitySystemComponent) return;

    FGameplayTagContainer AbilityTags;
    AbilityTags.AddTag(InputTag);
    AbilitySystemComponent->TryActivateAbilitiesByTag(AbilityTags);
}

void AProjectHPlayerCharacter::RotateToMouseCursor()
{
    AProjectHPlayerController* PC = Cast<AProjectHPlayerController>(GetController());
    if (!PC) return;

    FVector MouseWorldPos, MouseWorldDir;
    if (!PC->DeprojectMousePositionToWorld(MouseWorldPos, MouseWorldDir)) return;

    // 바닥에 레이캐스트해서 위치 구하기 (Z = 캐릭터 Z)
    FVector CharacterLoc = GetActorLocation();
    FVector PlaneIntersect = FMath::LinePlaneIntersection(
        MouseWorldPos, MouseWorldPos + MouseWorldDir * 10000.f,
        FVector(0.f, 0.f, CharacterLoc.Z),
        FVector::UpVector
    );

    FVector LookDir = PlaneIntersect - CharacterLoc;
    LookDir.Z = 0.f;
    if (LookDir.IsNearlyZero()) return;

    FRotator TargetRot = LookDir.Rotation();
    TargetRot.Yaw -= 90.f; // 메쉬 앞 방향 보정

    if (USkeletalMeshComponent* MeshComp = GetMesh())
    {
        FRotator NewRot = FMath::RInterpTo(MeshComp->GetComponentRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 10.f);
        MeshComp->SetWorldRotation(NewRot);
    }
}
