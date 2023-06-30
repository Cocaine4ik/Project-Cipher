// Project Cipher. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PCBaseCharacter.generated.h"

class UPCHealthComponent;

UCLASS()
class APCBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    APCBaseCharacter(const FObjectInitializer& ObjInit);

    virtual void BeginPlay() override;
    
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UPCHealthComponent* HealthComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* DeathAnimation;

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* TakeDamageAnimation;

private:
    void OnDeath();
    void OnTakeDamage();
};