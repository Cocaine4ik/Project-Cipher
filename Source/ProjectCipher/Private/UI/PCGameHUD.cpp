// Project Cipher. All Rights Reserved.


#include "UI/PCGameHUD.h"
#include "Engine/Canvas.h"

void APCGameHUD::DrawHUD()
{
    Super::DrawHUD();
    
    DrawCrossHair();
}

void APCGameHUD::DrawCrossHair()
{
    const int32 SizeX = Canvas->SizeX;
    const int32 SizeY = Canvas->SizeY;
    const TInterval<float> Center(SizeX * 0.5f, SizeY * 0.5f);
    
    DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);
    DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);

}