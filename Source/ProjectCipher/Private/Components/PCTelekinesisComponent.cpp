// Project Cipher. All Rights Reserved.


#include "Components/PCTelekinesisComponent.h"
#include "PCBaseCharacter.h"
#include "Kismet/KismetSystemLibrary.h"


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
    /*
    if(GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green,
            FString::Printf(TEXT("Telekinesis: %s"), bTelekinesis ? TEXT("True") : TEXT("False")));
    
    const auto Controller = GetPlayerController();
    const auto Start = Controller->PlayerCameraManager->GetCameraLocation();
    const auto End = Controller->PlayerCameraManager->GetActorForwardVector() * 1000;
    DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, -1.0f, 0, 2.0f);
    */
    DetectTelekineticObject();
}

void UPCTelekinesisComponent::Telekinesis()
{
    bTelekinesis ? Push() : Pull();
}

void UPCTelekinesisComponent::Zoom(bool bEnabled)
{
    const auto Character = GetBaseCharacter();
    if(!Character) return;
    
    const auto Controller = GetPlayerController();
    if(!Controller || !Controller->PlayerCameraManager) return;
    
    
    // Controller->PlayerCameraManager->SetFOV(FOVZoomAngle);

    if (bEnabled)
    {
        DefaultCameraFOV = Controller->PlayerCameraManager->GetFOVAngle();
        
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
    
    const auto Character = GetBaseCharacter();
    if(!Character) return;

    const auto Controller = GetPlayerController();
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
    if (!GetBaseCharacter()) return;
    GetBaseCharacter()->PlayAnimMontage(PullAnimation);
    Zoom(true);
    
}

void UPCTelekinesisComponent::Push()
{
    if(!bTelekinesis || !GetBaseCharacter()) return;
    GetBaseCharacter()->PlayAnimMontage(PushAnimation);
    Zoom(false);
}

void UPCTelekinesisComponent::DetectTelekineticObject()
{
    if(!GetWorld()) return;
    
    const auto Controller = GetPlayerController();
    if(!Controller || !Controller->PlayerCameraManager) return;
    
    const auto StartPoint = Controller->PlayerCameraManager->GetCameraLocation();
    const auto EndPoint = Controller->PlayerCameraManager->GetActorForwardVector() * DetectionDistance;

    FHitResult Result;
    TArray<AActor*> ActorsToIgnore;
    ActorsToIgnore.Add(GetOwner());
    
    const bool bHit = UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), StartPoint, EndPoint, DetectionRadius,
        DetectionObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, Result, true,
        FLinearColor::Red, FLinearColor::Red, 2.0f);

    if(GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green,
            FString::Printf(TEXT("Hit: %s"), bHit ? TEXT("True") : TEXT("False")));
    
}

APCBaseCharacter* UPCTelekinesisComponent::GetBaseCharacter() const
{
    return Cast<APCBaseCharacter>(GetOwner());
}

APlayerController* UPCTelekinesisComponent::GetPlayerController() const
{
    if (!GetBaseCharacter()) return nullptr; 
    return Cast<APlayerController>(GetBaseCharacter()->GetController());
}
