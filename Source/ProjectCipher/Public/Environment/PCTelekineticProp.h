// Project Cipher. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PCTelekineticProp.generated.h"

class UStaticMeshComponent;
class UTimelineComponent;
class USceneComponent;

UENUM()
enum class ETelekinesisState
{
    Default,
    Pulled,
    Pushed
};

UCLASS()
class PROJECTCIPHER_API APCTelekineticProp : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    APCTelekineticProp();
    void Highlight(bool bEnable);
    void Pull(USceneComponent& PullTargetComponent);
    void Push();
    
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components")
    UStaticMeshComponent* StaticMeshComponent;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Telekinesis")
    bool bHighlight = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Telekinesis")
    float LiftHeight = 200.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Telekinesis")
    UCurveFloat* MovementCurve;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Telekinesis")
    float PullSpeed = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Telekinesis")
    float PullRotation = 0.1f;
    
    UPROPERTY(VisibleAnywhere, Category = "Telekinesis")
    ETelekinesisState CurrentState;
    
    UTimelineComponent* LiftTimeLine;

    USceneComponent* PullTarget;
    
    UFUNCTION()
    void OnLiftingStart(float Value);

    UFUNCTION()
    void OnLiftingFinished();
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
private:
    FVector StartLiftPoint;
    FVector EndLiftPoint;
    
    void Lift();
    void InitializePull();
    void MoveToCharacter();
};