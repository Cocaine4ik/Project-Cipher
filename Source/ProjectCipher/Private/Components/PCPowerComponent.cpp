// Project Cipher. All Rights Reserved.


#include "Components/PCPowerComponent.h"

bool UPCPowerComponent::TryToUsePower(float PowerAmount)
{
    if (Value < PowerAmount) return false;

    SetValue(Value - PowerAmount);

    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta,
    FString::Printf(TEXT("Power Value: %f"), Value));
    return true;
}