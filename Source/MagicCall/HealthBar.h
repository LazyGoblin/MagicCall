#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "HealthBar.generated.h"

/**
 *
 */
UCLASS(Abstract)
class MAGICCALL_API UHealthBar : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    class UProgressBar *HealthBar;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock *CurrentHealthLabel;

public:
    void UpdateHealthBar(float CurrentHealth, float MaxHealth)
    {
        if (HealthBar)
        {
            float HealthPercentage = FMath::Clamp(CurrentHealth / MaxHealth, 0.0f, 1.0f);
            HealthBar->SetPercent(HealthPercentage);
        }

        if (CurrentHealthLabel)
        {
            FString HealthString = FString::Printf(TEXT("%.0f"), CurrentHealth);
            CurrentHealthLabel->SetText(FText::FromString(HealthString));
        }
    }
};