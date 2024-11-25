#include "PlayerCharacter.h"
#include "HealthBar.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

   // AutoPossessPlayer = EAutoReceiveInput::Player0;

    bAutoManageActiveCameraTarget = false;

    bUseControllerRotationYaw = false;

    HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
    HealthWidgetComponent->SetupAttachment(RootComponent);

    Health = MaxHealth;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APlayerCharacter::Fire()
{
    if (ProjectileClass)
    {
        FVector CharacterLocation = GetActorLocation();
        FRotator CharacterRotation = GetActorRotation();

        MuzzleOffset.Set(100.0f, 0.0f, 0.0f);

        FVector MuzzleLocation = CharacterLocation + FTransform(CharacterRotation).TransformVector(MuzzleOffset);

        FRotator MuzzleRotation = CharacterRotation;

        UWorld *World = GetWorld();
        if (World)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = GetInstigator();

            AProjectile *Projectile = World->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
            if (Projectile)
            {
                // Set the projectile's initial trajectory.
                FVector LaunchDirection = MuzzleRotation.Vector();
                Projectile->FireInDirection(LaunchDirection);
            }
        }
    }
}

void APlayerCharacter::LookAtCursor()
{
    FVector MouseLocation, MouseDirection;

    // Get the player controller
    APlayerController *PlayerController = Cast<APlayerController>(GetController());
    if (!PlayerController)
        return;
        
    PlayerController->bShowMouseCursor = true;
    // Get the hit result under the cursor
    FHitResult HitResult;
    PlayerController->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, HitResult);

    // If we hit something, update rotation
    if (HitResult.bBlockingHit)
    {
        FVector HitLocation = HitResult.ImpactPoint;
        FVector CharacterLocation = GetActorLocation();
        FRotator TargetRotation = (HitLocation - CharacterLocation).Rotation();

        // Modify rotation as needed
        FRotator NewRotation = FRotator(GetActorRotation().Pitch, TargetRotation.Yaw, GetActorRotation().Roll);

        // Set the new rotation
        SetActorRotation(NewRotation);
    }
}

float APlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    Health -= DamageAmount;
    if (Health <= 0)
    {
        Destroy();
    }
    
    if (HealthWidgetComponent && HealthWidgetComponent->GetUserWidgetObject())
    {
        UHealthBar* HealthBarWidget = Cast<UHealthBar>(HealthWidgetComponent->GetUserWidgetObject());
        if (HealthBarWidget)
        {
            HealthBarWidget->UpdateHealthBar(Health, MaxHealth);
        }
    }

     LaunchCharacter(FVector(0, 0, 500), false, false);
    
    return DamageAmount;
}