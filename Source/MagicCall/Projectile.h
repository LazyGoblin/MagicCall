// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.generated.h"

UCLASS()
class MAGICCALL_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectiles)
	USphereComponent *CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent *ProjectileMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectiles)
	UStaticMeshComponent *ProjectileMeshComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Movement)
	UMaterialInstanceDynamic *ProjectileMaterialInstance;

	void FireInDirection(const FVector &ShootDirection);

	UPROPERTY(EditDefaultsOnly)
	float BaseDamage = 10;

	UPROPERTY(EditDefaultsOnly)
	float ImpulseStrength = 100.0f;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType> BaseDamageType;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//Something private
};
