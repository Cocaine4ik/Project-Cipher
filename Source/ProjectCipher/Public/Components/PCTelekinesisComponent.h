// Project Cipher. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Player/PCCipherCharacter.h"
#include "PCTelekinesisComponent.generated.h"

class APCTelekineticProp;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTCIPHER_API UPCTelekinesisComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UPCTelekinesisComponent();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zoom")
    float FOVZoomAngle = 60.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zoom")
    float ZoomDuration = 0.5f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zoom")
    float ZoomFrequency = 0.25f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
    UAnimMontage* PullAnimation;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
    UAnimMontage* PushAnimation;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Telekinesis")
    float DetectionDistance = 3000.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Telekinesis")
    float DetectionRadius = 25.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Telekinesis")
    TArray<TEnumAsByte<EObjectTypeQuery>> DetectionObjectTypes;
    
    UFUNCTION(BlueprintCallable)
    bool IsTelekinesis() const { return bTelekinesis; }
    
    UFUNCTION(BlueprintCallable)
    void SetTelekinesis(bool Value) { bTelekinesis = Value; }
    
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void Telekinesis();

private:
    bool bTelekinesis = false;
    bool bZoom = false;
    
    float DefaultCameraFOV = 90.0f;
    float TargetCameraFOV;
    float InitialCameraFOV;
    FTimerHandle ZoomTimerHandle;
    float StartTime;

    APCTelekineticProp* CurrentProp;
    
    void Zoom(bool bEnabled);
    void ZoomUpdate();
    void Pull();
    void Push();

    void DetectTelekineticObject();
    
    APCCipherCharacter* GetCipherCharacter() const;
    APlayerController* GetPlayerController() const;
    
};