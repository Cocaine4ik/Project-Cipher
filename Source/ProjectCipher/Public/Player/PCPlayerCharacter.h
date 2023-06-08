// Project Cipher. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/PCCipherCharacter.h"
#include "PCPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UPCInteractionComponent;
/**
 * 
 */
UCLASS()
class PROJECTCIPHER_API APCPlayerCharacter : public APCCipherCharacter
{
    GENERATED_BODY()

public:
    APCPlayerCharacter(const FObjectInitializer& ObjInit);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interacion")
    TArray<TEnumAsByte<EObjectTypeQuery>> InteractableObjectTypes;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interaction")
    float InteractionRadius = 100.0f;

private:
    UPCInteractionComponent* CurrentInteractionComponent;
    
    void MoveForward(float Value);
    void MoveRight(float Value);
    void LookAround(float Value);
    void Interact();
    void DetectInteractableObject();

public:
    virtual void Tick(float DeltaSeconds) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
    USpringArmComponent* GetCameraBoom() const { return SpringArmComponent; }
    UCameraComponent* GetFollowCamera() const { return CameraComponent; }
};