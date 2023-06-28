// Project Cipher. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/PCBaseAttributeComponent.h"
#include "PCDelegates.h"
#include "PCHealthComponent.generated.h"

class UCameraShakeBase;

UCLASS()
class PROJECTCIPHER_API UPCHealthComponent : public UPCBaseAttributeComponent
{
    GENERATED_BODY()

public:
    UPCHealthComponent(const FObjectInitializer& ObjInit);

    FOnDeathSignature OnDeath;
    FOnTakeDamageSignature OnTakeDamage;
    
    UFUNCTION(BlueprintCallable, Category = "Health")
    bool IsDead() const { return Value <= 0.0f; }

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    TSubclassOf<UCameraShakeBase> CameraShake;

    virtual void BeginPlay() override;
    
private:
    UFUNCTION()
    void OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy,
    AActor* DamageCauser);

    void ApplyDamage(float Damage);
    void PlayCameraShake();
};