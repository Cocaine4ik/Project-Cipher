// Project Cipher. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/PCBaseWidget.h"
#include "PCPlayerHUDWidget.generated.h"

class UPCAttributeBarWidget;

UCLASS()
class PROJECTCIPHER_API UPCPlayerHUDWidget : public UPCBaseWidget
{
    GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;
    
protected:
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UPCBaseWidget* InteractionWidget;
    
private:
    UFUNCTION()
    void OnInteract(bool bEnable);

    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealthPercent() const;
    
    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetPowerPercent() const;
};