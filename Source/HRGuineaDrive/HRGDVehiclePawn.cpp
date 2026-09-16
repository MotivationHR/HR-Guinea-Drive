#include "HRGDVehiclePawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"

AHRGDVehiclePawn::AHRGDVehiclePawn(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    ChaseBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("ChaseBoom"));
    ChaseBoom->SetupAttachment(GetMesh());
    ChaseBoom->TargetArmLength = 520.0f;
    ChaseBoom->SetRelativeLocation(FVector(0.0f, 0.0f, 120.0f));
    ChaseBoom->bEnableCameraLag = true;
    ChaseBoom->CameraLagSpeed = 7.0f;

    ChaseCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ChaseCamera"));
    ChaseCamera->SetupAttachment(ChaseBoom, USpringArmComponent::SocketName);

    CockpitCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CockpitCamera"));
    CockpitCamera->SetupAttachment(GetMesh());
    CockpitCamera->SetRelativeLocation(FVector(20.0f, -32.0f, 112.0f));
    CockpitCamera->SetActive(false);
}

void AHRGDVehiclePawn::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (ULocalPlayer* LocalPlayer = PC->GetLocalPlayer())
        {
            if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
            {
                if (DrivingContext)
                {
                    Subsystem->AddMappingContext(DrivingContext, 0);
                }
            }
        }
    }
}

void AHRGDVehiclePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        if (ThrottleAction) EIC->BindAction(ThrottleAction, ETriggerEvent::Triggered, this, &AHRGDVehiclePawn::InputThrottle);
        if (ThrottleAction) EIC->BindAction(ThrottleAction, ETriggerEvent::Completed, this, &AHRGDVehiclePawn::InputThrottle);
        if (BrakeAction) EIC->BindAction(BrakeAction, ETriggerEvent::Triggered, this, &AHRGDVehiclePawn::InputBrake);
        if (BrakeAction) EIC->BindAction(BrakeAction, ETriggerEvent::Completed, this, &AHRGDVehiclePawn::InputBrake);
        if (SteeringAction) EIC->BindAction(SteeringAction, ETriggerEvent::Triggered, this, &AHRGDVehiclePawn::InputSteer);
        if (SteeringAction) EIC->BindAction(SteeringAction, ETriggerEvent::Completed, this, &AHRGDVehiclePawn::InputSteer);
        if (HandbrakeAction) EIC->BindAction(HandbrakeAction, ETriggerEvent::Started, this, &AHRGDVehiclePawn::InputHandbrakeStarted);
        if (HandbrakeAction) EIC->BindAction(HandbrakeAction, ETriggerEvent::Completed, this, &AHRGDVehiclePawn::InputHandbrakeCompleted);
        if (CameraAction) EIC->BindAction(CameraAction, ETriggerEvent::Started, this, &AHRGDVehiclePawn::InputCamera);
    }
}

void AHRGDVehiclePawn::InputThrottle(const FInputActionValue& Value)
{
    if (UChaosWheeledVehicleMovementComponent* Move = Cast<UChaosWheeledVehicleMovementComponent>(GetVehicleMovement()))
    {
        Move->SetThrottleInput(FMath::Clamp(Value.Get<float>(), 0.0f, 1.0f));
    }
}

void AHRGDVehiclePawn::InputBrake(const FInputActionValue& Value)
{
    if (UChaosWheeledVehicleMovementComponent* Move = Cast<UChaosWheeledVehicleMovementComponent>(GetVehicleMovement()))
    {
        Move->SetBrakeInput(FMath::Clamp(Value.Get<float>(), 0.0f, 1.0f));
    }
}

void AHRGDVehiclePawn::InputSteer(const FInputActionValue& Value)
{
    if (UChaosWheeledVehicleMovementComponent* Move = Cast<UChaosWheeledVehicleMovementComponent>(GetVehicleMovement()))
    {
        Move->SetSteeringInput(FMath::Clamp(Value.Get<float>(), -1.0f, 1.0f));
    }
}

void AHRGDVehiclePawn::InputHandbrakeStarted(const FInputActionValue&)
{
    if (UChaosWheeledVehicleMovementComponent* Move = Cast<UChaosWheeledVehicleMovementComponent>(GetVehicleMovement()))
    {
        Move->SetHandbrakeInput(true);
    }
}

void AHRGDVehiclePawn::InputHandbrakeCompleted(const FInputActionValue&)
{
    if (UChaosWheeledVehicleMovementComponent* Move = Cast<UChaosWheeledVehicleMovementComponent>(GetVehicleMovement()))
    {
        Move->SetHandbrakeInput(false);
    }
}

void AHRGDVehiclePawn::InputCamera(const FInputActionValue&)
{
    SetCockpitView(!bCockpitView);
}

void AHRGDVehiclePawn::SetCockpitView(bool bEnabled)
{
    bCockpitView = bEnabled;
    CockpitCamera->SetActive(bEnabled);
    ChaseCamera->SetActive(!bEnabled);
}