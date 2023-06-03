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

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UPCHealthComponent* HealthComponent;
};