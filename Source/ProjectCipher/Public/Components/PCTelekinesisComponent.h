// Project Cipher. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Player/PCCipherCharacter.h"
#include "PCTelekinesisComponent.generated.h"

class APCTelekineticProp;
class USpringArmComponent;
class UCharacterMovementComponent;
class UPCHealthComponent;
class UPCPowerComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTCIPHER_API UPCTelekinesisComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UPCTelekinesisComponent();

    UFUNCTION(BlueprintCallable)
    bool IsTelekinesis() const { return bTelekinesis; }

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zoom")
    float CameraOffsetX = 160.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zoom")
    float CameraOffsetY = 50.0f;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zoom")
    float ZoomDuration = 0.4f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zoom")
    float ZoomFrequency = 0.25f;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
    UAnimMontage* PullAnimation;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
    UAnimMontage* PushAnimation;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Telekinesis")
    float DetectionDistance = 3000.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Telekinesis")
    float PushDistance = 3000.0f;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Telekinesis")
    float DetectionRadius = 25.0f;    
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Telekinesis")
    TArray<TEnumAsByte<EObjectTypeQuery>> DetectionObjectTypes;
    
    UFUNCTION(BlueprintCallable)
    void SetTelekinesis(bool Value) { bTelekinesis = Value; }
    
    UFUNCTION(BlueprintCallable)
    void SetCanPush(bool Value) { bCanPush = Value; }
    
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void Telekinesis();

private:
    USpringArmComponent* SpringArmComponent;
    UCharacterMovementComponent* CharacterMovementComponent;
    UPCHealthComponent* HealthComponent;
    UPCPowerComponent* PowerComponent;
    
    bool bTelekinesis = false;
    bool bCanPush = false;
    
    bool bZoom = false;

    float DefaultSpeed;
    
    FVector DefaultCameraPosition;
    FVector TargetCameraPosition;
    FVector InitialCameraPosition;
    
    FTimerHandle ZoomTimerHandle;
    float StartTime;

    APCTelekineticProp* DetectedProp;
    APCTelekineticProp* PulledProp;
    
    void Zoom(bool bEnabled);
    void ZoomUpdate();
    void Pull();
    void Push();

    void DetectTelekineticObject();
    
    APCCipherCharacter* GetCipherCharacter() const;
    APlayerController* GetPlayerController() const;
    
};