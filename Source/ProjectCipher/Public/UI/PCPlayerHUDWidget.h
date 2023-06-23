// Project Cipher. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/PCBaseWidget.h"
#include "PCPlayerHUDWidget.generated.h"

UCLASS()
class PROJECTCIPHER_API UPCPlayerHUDWidget : public UPCBaseWidget
{
    GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;
    
protected:
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UPCBaseWidget* InteractionWidget;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UPCBaseWidget* HealthProgressBar;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UPCBaseWidget* PowerProgressBar;
    
private:
    UFUNCTION()
    void OnInteract(bool bEnable);
};