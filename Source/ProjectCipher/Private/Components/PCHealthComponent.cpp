// Project Cipher. All Rights Reserved.


#include "Components/PCHealthComponent.h"

#include "PCPlayerCharacter.h"
#include "PCPlayerController.h"
#include "Components/Slider.h"

UPCHealthComponent::UPCHealthComponent(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
}

void UPCHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UPCHealthComponent::OnTakeAnyDamageHandle);
}

void UPCHealthComponent::OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy,
    AActor* DamageCauser)
{
    ApplyDamage(Damage);
}

void UPCHealthComponent::ApplyDamage(float Damage)
{
    if (Damage <= 0.0f || IsDead() || !GetWorld()) return;

    SetValue(Value - Damage);

    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red,
        FString::Printf(TEXT("Health: %f"), Value));

    GetWorld()->GetTimerManager().ClearTimer(AutoRestorationTimerHandle);

    if (IsDead())
    {
        OnDeath.Broadcast();
    }
    else if (bAutoRestoration && GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(AutoRestorationTimerHandle, this, &UPCHealthComponent::AutoRestorationUpdate,
            RestorationUpdateTime, true, RestorationDelay);
    }

    PlayCameraShake();
}

void UPCHealthComponent::PlayCameraShake()
{
    if(IsDead()) return;

    const auto Player = Cast<APawn>(GetOwner());
    if(!Player) return;

    const auto Controller = Player->GetController<APCPlayerController>();
    if(!Controller || !Controller->PlayerCameraManager) return;

    Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}