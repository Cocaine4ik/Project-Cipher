// Project Cipher. All Rights Reserved.


#include "Components/PCBaseAttributeComponent.h"

// Sets default values for this component's properties
UPCBaseAttributeComponent::UPCBaseAttributeComponent(const FObjectInitializer& ObjInit)
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

bool UPCBaseAttributeComponent::TryToAddValue(float ValueAmount)
{
    if(IsValueFull()) return false;

    SetValue(Value + ValueAmount);
    return true;
}

bool UPCBaseAttributeComponent::IsValueFull() const
{
    return FMath::IsNearlyEqual(Value, MaxValue);
}

void UPCBaseAttributeComponent::SetValue(const float NewValue)
{
    const auto NextValue = FMath::Clamp(NewValue, 0.0f, MaxValue);
    const auto ValueDelta = NextValue - Value;
    Value = NextValue;
    
    OnValueChanged.Broadcast(Value, ValueDelta);
}

void UPCBaseAttributeComponent::AutoRestorationUpdate()
{
    SetValue(Value + RestorationModifier);

    if(IsValueFull() && GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(AutoRestorationTimerHandle);
    }
}


// Called when the game starts
void UPCBaseAttributeComponent::BeginPlay()
{
    Super::BeginPlay();

    check(MaxValue > 0)

    SetValue(MaxValue);
    
}


// Called every frame
void UPCBaseAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}