// Project Cipher. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PCGameHUD.generated.h"

class UPCBaseWidget;

UCLASS()
class PROJECTCIPHER_API APCGameHUD : public AHUD
{
    GENERATED_BODY()
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CrossHair")
    float HalfLineSize = 10.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CrossHair")
    float LineThickness = 2.0f;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CrossHair")
    FLinearColor LineColor;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerHUDWidgetClass;
    
public:
    virtual void DrawHUD() override;
    
private:
    void DrawCrossHair();
    
};