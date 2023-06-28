// Project Cipher. All Rights Reserved.

#include "Player/PCCipherCharacter.h"

#include "PCHealthComponent.h"
#include "Components/InputComponent.h"
#include "Components/PCTelekinesisComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Components/PCTelekinesisComponent.h"
#include "Components/SceneComponent.h"
#include "Components/PCPowerComponent.h"
#include "Components/TimelineComponent.h"

APCCipherCharacter::APCCipherCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = true;            // Character moves in the direction of input...	
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

    // Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
    // instead of recompiling to adjust them
    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = MaxRunSpeed;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;

    TelekinesisComponent = CreateDefaultSubobject<UPCTelekinesisComponent>(TEXT("TelekinesisComponent"));

    // Create pull place and attach it to static mesh 
    PullTarget = CreateDefaultSubobject<USceneComponent>(TEXT("PullTarget"));
    PullTarget->SetupAttachment(GetMesh());

    PowerComponent = CreateDefaultSubobject<UPCPowerComponent>(TEXT("PowerComponent"));

    DodgeTimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("DodgeTimeLine"));
}

void APCCipherCharacter::Dodge()
{

    if (TelekinesisComponent->IsTelekinesis() || !DodgeAnimation || !bCanDodge || HealthComponent->IsDead()) return;
    bCanDodge = false;
    PlayAnimMontage(DodgeAnimation);

    FOnTimelineFloat DodgeTimelineStartEvent;
    //DodgeTimeLine->SetTimelineLength(0.5f);
    DodgeTimelineStartEvent.BindUFunction(this, "OnDodgeStart");

    if(DodgeCurve)
    {
        DodgeTimeLine->AddInterpFloat(DodgeCurve, DodgeTimelineStartEvent);
    }

    DodgeTimeLine->PlayFromStart();

    
}

void APCCipherCharacter::OnDodgeStart()
{
    auto Velocity = GetActorForwardVector() * DodgeDistance;;
    Velocity.Z = GetCharacterMovement()->Velocity.Z;
    GetCharacterMovement()->Velocity = Velocity;

}