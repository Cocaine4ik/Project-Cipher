// Project Cipher. All Rights Reserved.

#include "Player/PCCipherCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/PCTelekinesisComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/PCTelekinesisComponent.h"
#include "Components/SceneComponent.h"

APCCipherCharacter::APCCipherCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
    // Don't rotate when the controller rotates. Let that just affect the camera.
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = true;            // Character moves in the direction of input...	
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

    // Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
    // instead of recompiling to adjust them
    GetCharacterMovement()->MaxWalkSpeed = 500.f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

    // Create a camera boom (pulls in towards the player if there is a collision)
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
    SpringArmComponent->SetupAttachment(RootComponent);
    SpringArmComponent->TargetArmLength = 400.0f;       // The camera follows at this distance behind the character	
    SpringArmComponent->bUsePawnControlRotation = true; // Rotate the arm based on the controller

    // Create a follow camera
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
    
    // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
    CameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

    TelekinesisComponent = CreateDefaultSubobject<UPCTelekinesisComponent>(TEXT("TelekinesisComponent"));

    // Create pull place and attach it to static mesh 
    PullTarget = CreateDefaultSubobject<USceneComponent>(TEXT("PullTarget"));
    PullTarget->SetupAttachment(GetMesh());
    
}

void APCCipherCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    PlayerInputComponent->BindAxis("MoveForward", this, &APCCipherCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &APCCipherCharacter::MoveRight);
    PlayerInputComponent->BindAxis("TurnRight", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAction("Telekinesis", IE_Pressed, TelekinesisComponent, &UPCTelekinesisComponent::Telekinesis);
}

void APCCipherCharacter::MoveForward(float Value)
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

void APCCipherCharacter::MoveRight(float Value)
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