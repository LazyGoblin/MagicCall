// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class APlayerCharacter;

UCLASS()
class MAGICCALL_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController();

	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void CallLookAtCursor();

	void CallFire();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	FVector RightVector = FVector(0.0f, 1.0f, 0.0f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	FVector ForwardVector = FVector(1.0f, 0.0f, 0.0f);

private:
	void HorizontalMove(float value);
	void VerticalMove(float value);
	void HorizontalRotation(float value);

	APlayerCharacter* PlayerCharacterInstance;
};
