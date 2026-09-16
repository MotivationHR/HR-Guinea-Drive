#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HRGDSaveSubsystem.generated.h"

class UHRGDSaveGame;

UCLASS()
class HRGUINEADRIVE_API UHRGDSaveSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="HR Guinea Drive|Save")
    UHRGDSaveGame* LoadOrCreate();

    UFUNCTION(BlueprintCallable, Category="HR Guinea Drive|Save")
    bool SaveNow();

    UFUNCTION(BlueprintPure, Category="HR Guinea Drive|Save")
    UHRGDSaveGame* GetCurrentSave() const { return CurrentSave; }

    UFUNCTION(BlueprintCallable, Category="HR Guinea Drive|Save")
    void ResetToNewLocalProfile();

private:
    UPROPERTY() TObjectPtr<UHRGDSaveGame> CurrentSave;
    static const FString SlotName;
    static constexpr int32 UserIndex = 0;
};