// Project Cipher. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PCBaseCharacter.generated.h"

class UPCTelekinesisComponent;

UCLASS()
class APCBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    APCBaseCharacter();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UPCTelekinesisComponent* TelekinesisComponent;
    
    /** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
    float TurnRateGamepad;

private:
    
    void MoveForward(float Value);
    void MoveRight(float Value);
    void Telekinesis();

public:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    USpringArmComponent* GetCameraBoom() const { return SpringArmComponent; }
    UCameraComponent* GetFollowCamera() const { return CameraComponent; }
};