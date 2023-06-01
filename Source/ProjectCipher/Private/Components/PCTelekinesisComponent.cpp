// Project Cipher. All Rights Reserved.


#include "Components/PCTelekinesisComponent.h"
#include "PCCipherCharacter.h"
#include "Environment/PCTelekineticProp.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Environment/PCTelekineticProp.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogTelekinesisComponent, All, All)

// Sets default values for this component's properties
UPCTelekinesisComponent::UPCTelekinesisComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UPCTelekinesisComponent::BeginPlay()
{
    Super::BeginPlay();

    SpringArmComponent = Cast<USpringArmComponent>(
        GetOwner()->GetComponentByClass(USpringArmComponent::StaticClass()));

    CharacterMovementComponent = Cast<UCharacterMovementComponent>(
    GetOwner()->GetComponentByClass(UCharacterMovementComponent::StaticClass()));
}


// Called every frame
void UPCTelekinesisComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    DetectTelekineticObject();
}

void UPCTelekinesisComponent::Telekinesis()
{
    bTelekinesis ? Push() : Pull();
}

void UPCTelekinesisComponent::Zoom(bool bEnabled)
{

    if (!SpringArmComponent)
    {
        return;
    }

    if (bEnabled)
    {
        DefaultCameraPosition = SpringArmComponent->GetRelativeLocation();

        bZoom = true;
        
        // Initialize target camera position using zoom angle and camera offset
        TargetCameraPosition = DefaultCameraPosition;
        TargetCameraPosition.X += CameraOffsetX;
        TargetCameraPosition.Y -= CameraOffsetY;
        
        InitialCameraPosition = DefaultCameraPosition;
        
        StartTime = GetWorld()->GetTimeSeconds();

        GetWorld()->GetTimerManager().SetTimer(ZoomTimerHandle, this, &UPCTelekinesisComponent::ZoomUpdate, ZoomFrequency, true);
    }
    else
    {
        bZoom = false;
        TargetCameraPosition = DefaultCameraPosition;
        InitialCameraPosition = SpringArmComponent->GetRelativeLocation();
        StartTime = GetWorld()->GetTimeSeconds();

        GetWorld()->GetTimerManager().SetTimer(ZoomTimerHandle, this, &UPCTelekinesisComponent::ZoomUpdate, ZoomFrequency, true);

    }
}

void UPCTelekinesisComponent::ZoomUpdate()
{
    
    const float CurrentTime = GetWorld()->GetTimeSeconds();
    const float Alpha = FMath::Clamp((CurrentTime - StartTime) / ZoomDuration, 0.0f, 1.0f);
    const FVector NewCameraPosition = FMath::Lerp(InitialCameraPosition, TargetCameraPosition, Alpha);
    
    SpringArmComponent->SetRelativeLocation(NewCameraPosition);

    if (Alpha >= 1.0f)
    {
        GetWorld()->GetTimerManager().ClearTimer(ZoomTimerHandle);
    }
}

void UPCTelekinesisComponent::Pull()
{
    if (!GetCipherCharacter() || !DetectedProp)
    {
        return;
    }
    DefaultSpeed = GetCipherCharacter()->GetMaxRunSpeed();
    CharacterMovementComponent->MaxWalkSpeed = GetCipherCharacter()->GetMaxWalkSpeed();
    
    GetCipherCharacter()->PlayAnimMontage(PullAnimation);
    Zoom(true);

    DetectedProp->Highlight(false);
    DetectedProp->Pull(*GetCipherCharacter()->GetPullTarget());
    PulledProp = DetectedProp;
}

void UPCTelekinesisComponent::Push()
{
    if (!bTelekinesis || !GetCipherCharacter() || !GetWorld())
    {
        return;
    }

    Zoom(false);
    
    FHitResult Result;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());

    // Calculate start and and points, make line trace
    const auto StartPoint = SpringArmComponent->GetComponentLocation();
    const auto EndPoint = SpringArmComponent->GetComponentLocation()
    + SpringArmComponent->GetForwardVector() * PushDistance;
    const bool bHit = GetWorld()->LineTraceSingleByChannel(Result, StartPoint, EndPoint, ECC_Visibility, CollisionParams);
    
    if (Result.bBlockingHit)
    {
        PulledProp->Push(Result);
        PulledProp = nullptr;
    }
    
    GetCipherCharacter()->PlayAnimMontage(PushAnimation);

    CharacterMovementComponent->MaxWalkSpeed = DefaultSpeed;
}

void UPCTelekinesisComponent::DetectTelekineticObject()
{
    if (!GetWorld())
    {
        return;
    }

    const auto Controller = GetPlayerController();
    if (!Controller || !Controller->PlayerCameraManager)
    {
        return;
    }

    const auto StartPoint = Controller->PlayerCameraManager->GetCameraLocation()
                            + Controller->PlayerCameraManager->GetActorForwardVector() * DetectionRadius;

    const auto EndPoint = Controller->PlayerCameraManager->GetCameraLocation()
                          + Controller->PlayerCameraManager->GetActorForwardVector() * DetectionDistance;

    FHitResult Result;
    TArray<AActor*> ActorsToIgnore;
    ActorsToIgnore.Add(GetOwner());

    const bool bHit = UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), StartPoint, EndPoint, DetectionRadius,
        DetectionObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, Result, true,
        FLinearColor::Red, FLinearColor::Red, 1.0f);

    if (GEngine)
    {/*
        GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green,
            FString::Printf(TEXT("Hit: %s"), bHit ? TEXT("True") : TEXT("False")));*/
    }

    if (Result.IsValidBlockingHit())
    {
        if (!DetectedProp)
        {
            DetectedProp = Cast<APCTelekineticProp>(Result.GetActor());
            DetectedProp->Highlight(true);
        }
        else if (DetectedProp->GetName() != Cast<APCTelekineticProp>(Result.GetActor())->GetName())
        {
            DetectedProp->Highlight(false);
            DetectedProp = Cast<APCTelekineticProp>(Result.GetActor());
            DetectedProp->Highlight(true);
        }
    }
    else
    {
        if (DetectedProp)
        {
            DetectedProp->Highlight(false);
            DetectedProp = nullptr;
        }
    }
}

APCCipherCharacter* UPCTelekinesisComponent::GetCipherCharacter() const
{
    return Cast<APCCipherCharacter>(GetOwner());
}

APlayerController* UPCTelekinesisComponent::GetPlayerController() const
{
    if (!GetCipherCharacter())
    {
        return nullptr;
    }
    return Cast<APlayerController>(GetCipherCharacter()->GetController());
}