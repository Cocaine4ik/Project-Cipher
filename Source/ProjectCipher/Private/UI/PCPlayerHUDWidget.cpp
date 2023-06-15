// Project Cipher. All Rights Reserved.


#include "UI/PCPlayerHUDWidget.h"

#include "FileHelpers.h"
#include "Player/PCPlayerCharacter.h"

void UPCPlayerHUDWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    InteractionWidget->AddToViewport();
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