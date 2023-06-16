// Project Cipher. All Rights Reserved.


#include "UI/PCPlayerHUDWidget.h"

#include "FileHelpers.h"
#include "Player/PCPlayerCharacter.h"

void UPCPlayerHUDWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    
    InteractionWidget->SetVisibility(ESlateVisibility::Hidden);
    
    HealthProgressBar->SetVisibility(ESlateVisibility::Visible);
    
    PowerProgressBar->SetVisibility(ESlateVisibility::Visible);
    
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