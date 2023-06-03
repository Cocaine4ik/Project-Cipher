// Project Cipher. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/PCBaseAttributeComponent.h"
#include "PCHealthComponent.generated.h"

class UCameraShakeBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);

UCLASS()
class PROJECTCIPHER_API UPCHealthComponent : public UPCBaseAttributeComponent
{
    GENERATED_BODY()

public:
    UPCHealthComponent(const FObjectInitializer& ObjInit);

    FOnDeathSignature OnDeath;

    UFUNCTION(BlueprintCallable, Category = "Health")
    bool IsDead() const { return Value <= 0.0f; }

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    TSubclassOf<UCameraShakeBase> CameraShake;
};