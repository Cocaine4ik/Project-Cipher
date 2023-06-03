// Project Cipher. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/PCBaseCharacter.h"
#include "PCCipherCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UPCTelekinesisComponent;
class USceneComponent;
class UPCPowerComponent;
class UAnimMontage;
class UTimelineComponent;

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
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UPCPowerComponent* PowerComponent;
    
    UPROPERTY(EditAnywhere,Category = "Components")
    USceneComponent* PullTarget;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animations")
    UAnimMontage* DodgeAnimation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    UCurveFloat* DodgeCurve;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Input")
    float YawInputScale = 2.5f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Movement")
    float MaxRunSpeed = 700.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
    float MaxWalkSpeed = 200.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
    float DodgeDistance = 900.0f;
    
    UFUNCTION()
    void OnDodgeStart();

    UFUNCTION(BlueprintCallable)
    void SetCanDodge(bool Value) { bCanDodge = Value; }
    
private:
    UTimelineComponent* DodgeTimeLine;

    bool bCanDodge = true;
    
    void MoveForward(float Value);
    void MoveRight(float Value);
    void LookAround(float Value);
    void Dodge();

public:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    USpringArmComponent* GetCameraBoom() const { return SpringArmComponent; }
    UCameraComponent* GetFollowCamera() const { return CameraComponent; }
    USceneComponent* GetPullTarget() const {return PullTarget; }

    float GetMaxRunSpeed() const { return MaxRunSpeed; }
    float GetMaxWalkSpeed() const { return MaxWalkSpeed; }
};