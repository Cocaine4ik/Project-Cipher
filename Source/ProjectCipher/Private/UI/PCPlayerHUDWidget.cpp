// Project Cipher. All Rights Reserved.


#include "UI/PCPlayerHUDWidget.h"

#include "FileHelpers.h"
#include "Components/PCHealthComponent.h"
#include "Components/PCPowerComponent.h"
#include "Player/PCPlayerCharacter.h"
#include "UI/PCAttributeBarWidget.h"

void UPCPlayerHUDWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    
    InteractionWidget->SetVisibility(ESlateVisibility::Hidden);
    
    if(GetOwningPlayer())
    {
        const auto Player = Cast<APCPlayerCharacter>(GetOwningPlayer()->GetPawn());
        Player->OnInteract.AddUObject(this, &UPCPlayerHUDWidget::OnInteract);
    }
}

void UPCPlayerHUDWidget::OnInteract(bool bEnable)
{
    bEnable ? InteractionWidget->SetVisibility(ESlateVisibility::Visible) :
    InteractionWidget->SetVisibility(ESlateVisibility::Hidden);
}

float UPCPlayerHUDWidget::GetHealthPercent() const
{
    const auto Player = GetOwningPlayer()->GetPawn();
    if (!Player) return 0.0f;
    
    const auto HealthComponent = Cast<UPCHealthComponent>(
    Player->GetComponentByClass(UPCHealthComponent::StaticClass()));
    if(!HealthComponent) return 0.0f;
    
    return HealthComponent->GetAttributePercent();
}

float UPCPlayerHUDWidget::GetPowerPercent() const
{
    const auto Player = GetOwningPlayer()->GetPawn();
    if (!Player) return 0.0f;

    const auto PowerComponent = Cast<UPCPowerComponent>(
    Player->GetComponentByClass(UPCPowerComponent::StaticClass()));
    if(!PowerComponent) return 0.0f;

    return PowerComponent->GetAttributePercent();
}
