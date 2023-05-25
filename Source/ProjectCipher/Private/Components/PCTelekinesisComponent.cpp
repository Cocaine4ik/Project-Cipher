// Project Cipher. All Rights Reserved.


#include "Components/PCTelekinesisComponent.h"
#include "PCBaseCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogTelekinesisComponent, All, All)

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
    Zoom(true);

}

void UPCTelekinesisComponent::Zoom(bool bEnabled)
{
    if(!bTelekinesis) return;
    
    const auto Pawn = Cast<APawn>(GetOwner());
    if(!Pawn) return;
    
    const auto Controller = Cast<APlayerController>(Pawn->GetController());
    if(!Controller || !Controller->PlayerCameraManager) return;
    
    DefaultCameraFOV = Controller->PlayerCameraManager->GetFOVAngle();
    
    // Controller->PlayerCameraManager->SetFOV(FOVZoomAngle);

    if (bEnabled)
    {
        bZoom = true;
        TargetCameraFOV = FOVZoomAngle;
        InitialCameraFOV = Controller->PlayerCameraManager->GetFOVAngle();

        StartTime = GetWorld()->GetTimeSeconds();
        
        GetWorld()->GetTimerManager().SetTimer(ZoomTimerHandle, this, &UPCTelekinesisComponent::ZoomUpdate, ZoomFrequency, true);
    }
    else
    {
        bZoom = false;
        TargetCameraFOV = DefaultCameraFOV;
        InitialCameraFOV = Controller->PlayerCameraManager->GetFOVAngle();

        StartTime = GetWorld()->GetTimeSeconds();
        
        GetWorld()->GetTimerManager().SetTimer(ZoomTimerHandle, this, &UPCTelekinesisComponent::ZoomUpdate, ZoomFrequency, true);

    }
}

void UPCTelekinesisComponent::ZoomUpdate()
{
    const float CurrentTime = GetWorld()->GetTimeSeconds();
    const float Alpha = FMath::Clamp((CurrentTime - StartTime) / ZoomDuration, 0.0f, 1.0f);
    const float NewCameraFOV = FMath::Lerp(InitialCameraFOV, TargetCameraFOV, Alpha);
    
    const auto Pawn = Cast<APawn>(GetOwner());
    if(!Pawn) return;

    const auto Controller = Cast<APlayerController>(Pawn->GetController());
    if(!Controller || !Controller->PlayerCameraManager) return;
    
    Controller->PlayerCameraManager->SetFOV(NewCameraFOV);
    
    UE_LOG(LogTelekinesisComponent, Display, TEXT("NewCameraFOV: %f"), NewCameraFOV);
    
    if(Alpha >= 1.0f)
    {
        GetWorld()->GetTimerManager().ClearTimer(ZoomTimerHandle);
    }
}

void UPCTelekinesisComponent::Pull()
{
    if(!bTelekinesis) return;
    const auto Character = Cast<APCBaseCharacter>(GetOwner());
    Character->GetMesh()->PlayAnimation(PullAnimation, false);
}

void UPCTelekinesisComponent::Push()
{
}
