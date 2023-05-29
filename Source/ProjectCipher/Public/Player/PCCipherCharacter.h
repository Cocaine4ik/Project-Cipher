// Project Cipher. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/PCBaseCharacter.h"
#include "PCCipherCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UPCTelekinesisComponent;
class USceneComponent;

UCLASS()
class PROJECTCIPHER_API APCCipherCharacter : public APCBaseCharacter
{
    GENERATED_BODY()
    
public:
    APCCipherCharacter(const FObjectInitializer& ObjInit);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UPCTelekinesisComponent* TelekinesisComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(EditAnywhere,Category = "Components")
    USceneComponent* PullTarget;
    
private:
    void MoveForward(float Value);
    void MoveRight(float Value);

public:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    USpringArmComponent* GetCameraBoom() const { return SpringArmComponent; }
    UCameraComponent* GetFollowCamera() const { return CameraComponent; }
    USceneComponent* GetPullTarget() const {return PullTarget; }
};