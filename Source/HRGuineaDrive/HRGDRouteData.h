#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HRGDRouteData.generated.h"

UENUM(BlueprintType)
enum class EHRGDBiome : uint8
{
    Urban,
    Highland,
    Rural,
    Forest,
    Transition,
    Coastal
};

USTRUCT(BlueprintType)
struct FHRGDGeoAnchor
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly) FName Id;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) FText Label;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) double Latitude = 0.0;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) double Longitude = 0.0;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) float ElevationMeters = 0.0f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) EHRGDBiome Biome = EHRGDBiome::Rural;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) bool bRecognitionAnchor = false;
};

UCLASS(BlueprintType)
class HRGUINEADRIVE_API UHRGDRouteData : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly) FName RouteId;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) FText DisplayName;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) FName OriginId;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) FName DestinationId;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) float RealDistanceKm = 0.0f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) float TargetJourneyMinutes = 40.0f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FHRGDGeoAnchor> Anchors;
};