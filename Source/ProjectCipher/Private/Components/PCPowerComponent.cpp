// Project Cipher. All Rights Reserved.


#include "Components/PCPowerComponent.h"

bool UPCPowerComponent::TryToUsePower(float PowerAmount)
{
    if (Value < PowerAmount) return false;

    SetValue(Value - PowerAmount);

    GetWorld()->GetTimerManager().ClearTimer(AutoRestorationTimerHandle);
    
    if (bAutoRestoration && GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(AutoRestorationTimerHandle, this, &UPCPowerComponent::AutoRestorationUpdate,
            RestorationUpdateTime, true, RestorationDelay);
    }

    return true;
}