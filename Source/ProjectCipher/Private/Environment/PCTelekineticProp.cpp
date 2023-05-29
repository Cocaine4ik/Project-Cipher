// Project Cipher. All Rights Reserved.

#include "Environment/PCTelekineticProp.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TimelineComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
APCTelekineticProp::APCTelekineticProp()
{
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMeshComponent->SetupAttachment(RootComponent);
    StaticMeshComponent->SetCollisionProfileName("Telekinesis");
    
    StaticMeshComponent->SetCustomDepthStencilValue(0);

    LiftTimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("LiftTimeLine"));

    CurrentState = ETelekinesisState::Default;

    // Enable physics simulation
    StaticMeshComponent->SetSimulatePhysics(true);
    StaticMeshComponent->SetAngularDamping(2.0f);
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    
}

void APCTelekineticProp::Highlight(bool bEnable)
{
    if(!StaticMeshComponent) return;
    bHighlight = bEnable;

    if(bHighlight)
    {
        StaticMeshComponent->SetRenderCustomDepth(true);
        StaticMeshComponent->SetCustomDepthStencilValue(1);
    }
    else
    {
        StaticMeshComponent->SetRenderCustomDepth(false);
        StaticMeshComponent->SetCustomDepthStencilValue(0);
    }
    bHighlight ? StaticMeshComponent->CustomDepthStencilValue = 1 : StaticMeshComponent->CustomDepthStencilValue = 0;
}

void APCTelekineticProp::Pull(USceneComponent& PullTargetComponent)
{
    PullTarget = &PullTargetComponent;
    Lift();
}

void APCTelekineticProp::Lift()
{
    StartLiftPoint = EndLiftPoint = GetActorLocation();
    EndLiftPoint.Z += LiftHeight;

    FOnTimelineFloat TimeLineStartEvent;
    FOnTimelineEvent TimeLineFinishedEvent;

    TimeLineStartEvent.BindUFunction(this, FName("OnLiftingStart"));
    TimeLineFinishedEvent.BindUFunction(this, FName("OnLiftingFinished"));

    if(MovementCurve)
    {
        LiftTimeLine->AddInterpFloat(MovementCurve, TimeLineStartEvent); 
    }
    LiftTimeLine->SetTimelineFinishedFunc(TimeLineFinishedEvent);
    LiftTimeLine->PlayFromStart();
}

void APCTelekineticProp::InitializePull()
{
    StaticMeshComponent->SetEnableGravity(false);
    StaticMeshComponent->SetLinearDamping(20.0f);
    CurrentState = ETelekinesisState::Pulled;
}

void APCTelekineticProp::MoveToCharacter()
{
    if(PullTarget)
    {
        if(GetWorld())
        DrawDebugLine(GetWorld(), StaticMeshComponent->GetComponentLocation(), PullTarget->GetComponentLocation(),
            FColor::Orange, false, 0.1f);
        
        const auto Impulse = PullTarget->GetComponentLocation() - GetActorLocation();
        StaticMeshComponent->AddImpulse(Impulse * PullSpeed);
    }
}

void APCTelekineticProp::OnLiftingStart(float Value)
{
    auto NewLoc = FMath::Lerp(StartLiftPoint, EndLiftPoint, Value);
    SetActorLocation(NewLoc);
}

void APCTelekineticProp::OnLiftingFinished()
{

    InitializePull();
}

// Called when the game starts or when spawned
void APCTelekineticProp::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void APCTelekineticProp::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(CurrentState == ETelekinesisState::Pulled)
    {
        MoveToCharacter();

        // Add Rotation Effect
        AddActorLocalRotation(FRotator(PullRotation, PullRotation, PullRotation));
    }
}
