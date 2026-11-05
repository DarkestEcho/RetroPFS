#pragma once
#include "Types/RFPSTypes.h"
#include "Weapons/RFPSProjectile.h"

class UTextBlock;
class ACharacter;

class RFPSUtils
{
public:
	static FViewPoint GetPawnViewPoint( const APawn* Pawn );
	static FVector GetLineTraceDirection( const FViewPoint& ViewPoint, const float SpreadAngle );
	static FHitResult MakeLineTraceSingle( const UWorld* World, const FTraceData& TraceData );
	static FText GetTextFromInt( int32 Number );
	static void SetAmmoDataTextBlocks( UTextBlock* CurrentAmmo, UTextBlock* MaxAmmo, FAmmoData AmmoData );
	static void DrawDebugHitTrace( const UWorld* World, const FHitResult& HitResult, const FVector& LineStart );

	static void LaunchProjectile( UWorld* World, const TSubclassOf<ARFPSProjectile> ProjectileClass, AActor* Owner, const FHitResult& HitResult, const USceneComponent* FireStartPoint, const bool bShowDebugSphere = false );

	template <class T>
	static T* GetComponentFromActor( const AActor* Actor );
};

template <class T>
T* RFPSUtils::GetComponentFromActor( const AActor* Actor )
{
	if ( !Actor )
	{
		return nullptr;
	}
	return Cast<T>( Actor->GetComponentByClass( T::StaticClass() ) );
}
