// Project Cipher. All Rights Reserved.


#include "Components/PCInteractionComponent.h"

// Sets default values for this component's properties
UPCInteractionComponent::UPCInteractionComponent()
{
}


// Called when the game starts
void UPCInteractionComponent::BeginPlay()
{
    Super::BeginPlay();

}

void UPCInteractionComponent::Interact()
{
    bInteracted = true;
}