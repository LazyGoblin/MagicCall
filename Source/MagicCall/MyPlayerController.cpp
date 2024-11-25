// MyPlayerController.cpp

#include "MyPlayerController.h"
#include "PlayerCharacter.h"

AMyPlayerController::AMyPlayerController()
{
    
}

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();
    PlayerCharacterInstance = Cast<APlayerCharacter>(GetPawn());
}

void AMyPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAxis("Horizontal", this, &AMyPlayerController::HorizontalMove);
    InputComponent->BindAxis("Vertical", this, &AMyPlayerController::VerticalMove);
    InputComponent->BindAxis("Horizontal Rotation", this, &AMyPlayerController::HorizontalRotation);
    
    InputComponent->BindAction("Fire", IE_Pressed, this, &AMyPlayerController::CallFire);
}

void AMyPlayerController::HorizontalRotation(float value)
{
    if (PlayerCharacterInstance)
    {
        FRotator NewRotation = GetControlRotation();
        NewRotation.Yaw += value;
        SetControlRotation(NewRotation);
    }
    CallLookAtCursor();
}

void AMyPlayerController::HorizontalMove(float value)
{
    if (PlayerCharacterInstance)
    {
        PlayerCharacterInstance->AddMovementInput(RightVector, value);
    }
}

void AMyPlayerController::VerticalMove(float value)
{
    if (PlayerCharacterInstance)
    {
        PlayerCharacterInstance->AddMovementInput(ForwardVector, value);
    }
}

void AMyPlayerController::CallLookAtCursor()
{
    if (PlayerCharacterInstance)
    {
        PlayerCharacterInstance->LookAtCursor();
    }
}

void AMyPlayerController::CallFire()
{
    if (PlayerCharacterInstance)
    {
        PlayerCharacterInstance->Fire();
    }
}
