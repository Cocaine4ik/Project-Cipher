// Project Cipher. All Rights Reserved.

#include "Player/PCBaseCharacter.h"

#include "PCHealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/PCHealthComponent.h"

APCBaseCharacter::APCBaseCharacter(const FObjectInitializer& ObjInit)
: Super(ObjInit)
{
    // Set size for collision capsule
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
    
    // Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
    // instead of recompiling to adjust them
    GetCharacterMovement()->MaxWalkSpeed = 400.f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

    HealthComponent = CreateDefaultSubobject<UPCHealthComponent>(TEXT("HealthComponent"));
    
}

void APCBaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(HealthComponent);

    HealthComponent->OnDeath.AddUObject(this, &APCBaseCharacter::OnDeath);
    HealthComponent->OnTakeDamage.AddUObject(this, &APCBaseCharacter::OnTakeDamage);
    
}

void APCBaseCharacter::OnDeath()
{
    PlayAnimMontage(DeathAnimation);

    GetCharacterMovement()->DisableMovement();
        
}

void APCBaseCharacter::OnTakeDamage()
{
    if (!GetMesh()->GetAnimInstance()->Montage_IsPlaying(TakeDamageAnimation))
    {
        PlayAnimMontage(TakeDamageAnimation);
    }
}
