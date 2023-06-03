// Project Cipher. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PCBaseAttributeComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnValueChangeSignature, float, float)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTCIPHER_API UPCBaseAttributeComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UPCBaseAttributeComponent(const FObjectInitializer& ObjInit);

    FOnValueChangeSignature OnValueChanged;
    
    UFUNCTION(BlueprintCallable, Category = "Attribute")
    float GetAttributePercent() const { return Value / MaxValue; }

    float GetValue() const { return Value; }

    bool TryToAddValue(float ValueAmount);
    bool IsValueFull() const;
    
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attributes", meta=(ClampMin = "0", ClampMax = "1000"))
    float MaxValue = 100.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attributes")
    bool bAutoRestoration = false;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attributes", meta=(EditCondition = "bAutoRestoration"))
    float RestorationUpdateTime = 0.3f;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attributes", meta=(EditCondition = "bAutoRestoration"))
    float RestorationDelay = 3.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attributes", meta=(EditCondition = "bAutoRestoration"))
    float RestorationModifier = 3.0f;
    
    // Called when the game starts
    virtual void BeginPlay() override;

    float Value = 0.0f;
    FTimerHandle AutoRestorationTimerHandle;

    void SetValue(const float NewValue);

    void AutoRestorationUpdate();
    
    
public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    
};