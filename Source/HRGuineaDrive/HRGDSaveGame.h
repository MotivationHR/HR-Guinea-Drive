#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "HRGDSaveGame.generated.h"

USTRUCT(BlueprintType)
struct FHRGDCharacterSaveData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString PlayerName;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName GenderId = TEXT("m");
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName SkinToneId = TEXT("s3");
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName FacePresetId = TEXT("f1");
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName HairPresetId = TEXT("h1");
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName OutfitId = TEXT("casual_01");
};

UCLASS(BlueprintType)
class HRGUINEADRIVE_API UHRGDSaveGame : public USaveGame
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) int32 SaveVersion = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString LocalPlayerId;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FHRGDCharacterSaveData Character;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int64 BalanceGNF = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FName> OwnedVehicleIds;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName CurrentVehicleId = TEXT("verso_starter");
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName CurrentRouteId = TEXT("mamou_conakry");
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform VehicleTransform = FTransform::Identity;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) float RouteProgress = 0.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FName> DiscoveredLocations;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FDateTime UpdatedAt;
};