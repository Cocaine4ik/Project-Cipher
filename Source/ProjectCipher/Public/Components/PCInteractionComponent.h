// Project Cipher. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PCInteractionComponent.generated.h"



UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTCIPHER_API UPCInteractionComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPCInteractionComponent();
    
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interacion")
    bool MultiInteractable = false;

    UPROPERTY(VisibleAnywhere, Category = "Interaction")
    bool bInteracted = false;
    
    virtual void BeginPlay() override;

public:
    void Interact();

    bool IsInteracted() const { return bInteracted; }
};