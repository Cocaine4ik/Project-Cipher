// Project Cipher. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PCTelekineticProp.generated.h"

class UStaticMeshComponent;

UCLASS()
class PROJECTCIPHER_API APCTelekineticProp : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    APCTelekineticProp();

    void Highlight(bool bEnable);
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components")
    UStaticMeshComponent* StaticMeshComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Highlight")
    bool bHighlight = false;
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
};