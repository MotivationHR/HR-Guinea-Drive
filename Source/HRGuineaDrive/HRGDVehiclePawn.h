#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "InputActionValue.h"
#include "HRGDVehiclePawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputAction;
class UInputMappingContext;

UCLASS(Blueprintable)
class HRGUINEADRIVE_API AHRGDVehiclePawn : public AWheeledVehiclePawn
{
    GENERATED_BODY()

public:
    AHRGDVehiclePawn(const FObjectInitializer& ObjectInitializer);
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera") TObjectPtr<USpringArmComponent> ChaseBoom;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera") TObjectPtr<UCameraComponent> ChaseCamera;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera") TObjectPtr<UCameraComponent> CockpitCamera;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input") TObjectPtr<UInputMappingContext> DrivingContext;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input") TObjectPtr<UInputAction> ThrottleAction;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input") TObjectPtr<UInputAction> BrakeAction;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input") TObjectPtr<UInputAction> SteeringAction;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input") TObjectPtr<UInputAction> HandbrakeAction;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input") TObjectPtr<UInputAction> CameraAction;

    UFUNCTION(BlueprintCallable, Category="HR Guinea Drive|Camera")
    void SetCockpitView(bool bEnabled);

protected:
    void InputThrottle(const FInputActionValue& Value);
    void InputBrake(const FInputActionValue& Value);
    void InputSteer(const FInputActionValue& Value);
    void InputHandbrakeStarted(const FInputActionValue& Value);
    void InputHandbrakeCompleted(const FInputActionValue& Value);
    void InputCamera(const FInputActionValue& Value);

private:
    bool bCockpitView = false;
};