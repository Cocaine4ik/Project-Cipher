// Project Cipher. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/PCBaseAttributeComponent.h"
#include "PCPowerComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCIPHER_API UPCPowerComponent : public UPCBaseAttributeComponent
{
    GENERATED_BODY()

public:
    bool TryToUsePower(float PowerAmount);
};