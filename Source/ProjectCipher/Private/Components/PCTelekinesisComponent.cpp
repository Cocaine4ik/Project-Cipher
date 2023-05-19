// Project Cipher. All Rights Reserved.


#include "Components/PCTelekinesisComponent.h"

// Sets default values for this component's properties
UPCTelekinesisComponent::UPCTelekinesisComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}


// Called when the game starts
void UPCTelekinesisComponent::BeginPlay()
{
    Super::BeginPlay();

    // ...

}


// Called every frame
void UPCTelekinesisComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}

void UPCTelekinesisComponent::Telekinesis()
{
    bTelekinesis = true;
    Zoom();
}

void UPCTelekinesisComponent::Zoom()
{
    if(!bTelekinesis) return;
    
    const auto Pawn = Cast<APawn>(GetOwner());
    if(!Pawn) return;
    
    const auto Controller = Cast<APlayerController>(Pawn->GetController());
    if(!Controller || !Controller->PlayerCameraManager) return;
    
    DefaultCameraFOV = Controller->PlayerCameraManager->GetFOVAngle();
    
    Controller->PlayerCameraManager->SetFOV(FOVZoomAngle);
    bZoom = true;
}

void UPCTelekinesisComponent::Pull()
{
    if(!bTelekinesis) return;
    
}

void UPCTelekinesisComponent::Push()
{
}