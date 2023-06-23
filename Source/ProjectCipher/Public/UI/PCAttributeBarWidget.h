// Project Cipher. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/PCBaseWidget.h"
#include "PCAttributeBarWidget.generated.h"

class UProgressBar;

UCLASS()
class PROJECTCIPHER_API UPCAttributeBarWidget : public UPCBaseWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UProgressBar* AttributeProgressBar;
    
};