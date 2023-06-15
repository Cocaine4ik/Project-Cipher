// Project Cipher. All Rights Reserved.


#include "UI/PCGameHUD.h"

#include "PCBaseWidget.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PCPlayerCharacter.h"

void APCGameHUD::DrawHUD()
{
    Super::DrawHUD();
    
    DrawCrossHair();
}

void APCGameHUD::BeginPlay()
{
    Super::BeginPlay();

    const auto PlayerHUDWidget = CreateWidget<UPCBaseWidget>(GetWorld(), PlayerHUDWidgetClass);
    PlayerHUDWidget->AddToViewport();
    PlayerHUDWidget->SetVisibility(ESlateVisibility::Visible);
}

void APCGameHUD::DrawCrossHair()
{
    const int32 SizeX = Canvas->SizeX;
    const int32 SizeY = Canvas->SizeY;
    const TInterval<float> Center(SizeX * 0.5f, SizeY * 0.5f);
    
    DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);
    DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);

}