// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class MAGICCALL_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	UFUNCTION()
	void Fire();

	void LookAtCursor();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
    bool bAutoManageActiveCameraTarget; 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent *HealthWidgetComponent;

	UPROPERTY(EditAnywhere)
	float Health;

	float MaxHealth = 100.0f;
	float HealthTweenDirection;

	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const &DamageEvent,
		AController *EventInstigator,
		AActor *DamageCauser) override;

private:
//Some private stuff
};
