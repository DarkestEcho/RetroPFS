#pragma once

#include "RFPSTypes.generated.h"

class UWorld;

struct FViewPoint
{
	FVector Location { FVector::ZeroVector };
	FRotator Rotation { FRotator::ZeroRotator };
};

struct FTraceData
{
	FViewPoint ViewPoint {};
	float Distance { 0.0f };
	float SpreadAngleHorizontal { 0.0f };
	float SpreadAngleVertical { 0.0f };
	ECollisionChannel CollisionChannel { ECC_Visibility };
	TArray<const AActor*> IgnoredActors {};
	bool bShowDebugLine { false };
	FVector DebugLineStart { FVector::ZeroVector };
};

UENUM( BlueprintType )
enum class EAmmoType : uint8
{
	Bullets,
	Shells,
	Rockets,
	Cells,
	Count UMETA( Hidden ) // Should always be the last value
};

USTRUCT( BlueprintType )
struct FAmmoData
{
	GENERATED_BODY()

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Ammo", meta=(ClampMin=0) )
	int32 CurrentAmmo { 0 };

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Ammo", meta=(ClampMin=0) )
	int32 MaxAmmo { 0 };
};

DECLARE_MULTICAST_DELEGATE_TwoParams( FOnAmmoChangedSignature, EAmmoType, FAmmoData );
