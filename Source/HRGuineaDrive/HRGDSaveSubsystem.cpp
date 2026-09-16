#include "HRGDSaveSubsystem.h"
#include "HRGDSaveGame.h"
#include "Kismet/GameplayStatics.h"

const FString UHRGDSaveSubsystem::SlotName = TEXT("HRGuineaDrive_Local_01");

UHRGDSaveGame* UHRGDSaveSubsystem::LoadOrCreate()
{
    if (CurrentSave)
    {
        return CurrentSave;
    }

    if (UGameplayStatics::DoesSaveGameExist(SlotName, UserIndex))
    {
        CurrentSave = Cast<UHRGDSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));
    }

    if (!CurrentSave)
    {
        CurrentSave = Cast<UHRGDSaveGame>(UGameplayStatics::CreateSaveGameObject(UHRGDSaveGame::StaticClass()));
        CurrentSave->LocalPlayerId = FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphensLower);
        CurrentSave->OwnedVehicleIds = { TEXT("verso_starter") };
        CurrentSave->UpdatedAt = FDateTime::UtcNow();
    }

    return CurrentSave;
}

bool UHRGDSaveSubsystem::SaveNow()
{
    UHRGDSaveGame* Save = LoadOrCreate();
    Save->UpdatedAt = FDateTime::UtcNow();
    return UGameplayStatics::SaveGameToSlot(Save, SlotName, UserIndex);
}

void UHRGDSaveSubsystem::ResetToNewLocalProfile()
{
    UGameplayStatics::DeleteGameInSlot(SlotName, UserIndex);
    CurrentSave = nullptr;
    LoadOrCreate();
}