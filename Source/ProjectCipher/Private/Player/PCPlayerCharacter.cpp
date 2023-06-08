// Project Cipher. All Rights Reserved.

#include "Player/PCPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/PCTelekinesisComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/PCInteractionComponent.h"

APCPlayerCharacter::APCPlayerCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
    
    // Don't rotate when the controller rotates. Let that just affect the camera.
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // Create a camera boom (pulls in towards the player if there is a collision)
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
    SpringArmComponent->SetupAttachment(RootComponent);
    SpringArmComponent->TargetArmLength = 250.0f;       // The camera follows at this distance behind the character	
    SpringArmComponent->bUsePawnControlRotation = true; // Rotate the arm based on the controller
    SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 40.0f);

    // Create a follow camera
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
    
    // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
    CameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void APCPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    PlayerInputComponent->BindAxis("MoveForward", this, &APCPlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &APCPlayerCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookAround", this, &APCPlayerCharacter::LookAround);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAction("Telekinesis", IE_Pressed, TelekinesisComponent, &UPCTelekinesisComponent::Telekinesis);
    PlayerInputComponent->BindAction("Dodge", IE_Pressed, this, &APCPlayerCharacter::Dodge);
    PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APCPlayerCharacter::Interact);
}

void APCPlayerCharacter::MoveForward(float Value)
{
    if (Controller != nullptr && Value != 0.0f)
    {
        // find out which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // get forward vector
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
    
}

void APCPlayerCharacter::MoveRight(float Value)
{
    if (Controller != nullptr && Value != 0.0f)
    {
        // find out which way is right
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // get right vector 
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        // add movement in that direction
        AddMovementInput(Direction, Value);
    }
}

void APCPlayerCharacter::LookAround(float Value)
{
    if (Controller != nullptr && Value != 0.0f)
    {
        // find out which way is right
        const FRotator Rotation = Controller->GetControlRotation();
        AddControllerYawInput(Value);
        
        if (TelekinesisComponent && TelekinesisComponent->IsTelekinesis())
        {
            AddActorWorldRotation(FRotator(0.0f, Value * YawInputScale, 0.0f));
        }
    }
}

void APCPlayerCharacter::Interact()
{
    if (TelekinesisComponent->IsTelekinesis()) return;
    
    if (CurrentInteractionComponent && !CurrentInteractionComponent->IsInteracted())
    {
        CurrentInteractionComponent->Interact();
    }
}

void APCPlayerCharacter::DetectInteractableObject()
{
    if(!GetWorld()) return;
    
    if(!GetController()) return;
    
    FHitResult Result;
    TArray<AActor*> ActorsToIgnore;
    ActorsToIgnore.Add(this);
    
    const auto StartPoint = GetActorLocation();
    const auto EndPoint = GetActorLocation();
    const bool bHit = UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), StartPoint, EndPoint, InteractionRadius, InteractableObjectTypes,
        false, ActorsToIgnore, EDrawDebugTrace::ForDuration, Result, true, FLinearColor::Green,
        FLinearColor::Green, 1.0f);
    
    if(bHit)
    {
        const auto NewInteractionComponent = Cast<UPCInteractionComponent>(Result.GetActor()->GetComponentByClass(UPCInteractionComponent::StaticClass()));
        if (NewInteractionComponent && NewInteractionComponent != CurrentInteractionComponent && !NewInteractionComponent->IsInteracted())
        {
            CurrentInteractionComponent = NewInteractionComponent;
        } 
        if (CurrentInteractionComponent) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green,
            FString::Printf(TEXT("Interactable: %s"), *Result.GetActor()->GetName()));
        
    }
    else if (CurrentInteractionComponent)
    {
        CurrentInteractionComponent = nullptr;
    }
}

void APCPlayerCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    DetectInteractableObject();
}