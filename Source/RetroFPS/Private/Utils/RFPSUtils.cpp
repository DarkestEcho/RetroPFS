#include "Utils/RFPSUtils.h"

#include "Components/TextBlock.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"


FViewPoint RFPSUtils::GetPawnViewPoint( const APawn* Pawn )
{
	FViewPoint ViewPoint {};
	if ( IsValid( Pawn ) )
	{
		if ( const AController* Controller = Pawn->GetController(); IsValid( Controller ) )
		{
			Controller->GetPlayerViewPoint( ViewPoint.Location, ViewPoint.Rotation );
		}
	}
	return ViewPoint;
}

FVector RFPSUtils::GetLineTraceDirection( const FViewPoint& ViewPoint, const float SpreadAngleHorizontal, const float SpreadAngleVertical )
{
	if ( SpreadAngleHorizontal > 0.0f || SpreadAngleVertical > 0.0f )
	{
		const float HalfRadiansHorizontal = FMath::DegreesToRadians( SpreadAngleHorizontal ) / 2.0f;
		const float HalfRadiansVertical = FMath::DegreesToRadians( SpreadAngleVertical ) / 2.0f;
		return FMath::VRandCone( ViewPoint.Rotation.Vector(), HalfRadiansHorizontal, HalfRadiansVertical );
	}
	return ViewPoint.Rotation.Vector();
}


FHitResult RFPSUtils::MakeLineTraceSingle( const UWorld* World, const FTraceData& TraceData )
{
	FHitResult HitResult {};
	if ( IsValid( World ) )
	{
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActors( TraceData.IgnoredActors );

		const FVector TraceStart { TraceData.ViewPoint.Location };
		const FVector TraceDirection { GetLineTraceDirection( TraceData.ViewPoint, TraceData.SpreadAngleHorizontal, TraceData.SpreadAngleVertical ) };
		const FVector TraceEnd { TraceData.ViewPoint.Location + TraceDirection * TraceData.Distance };

		World->LineTraceSingleByChannel(
			HitResult,
			TraceStart,
			TraceEnd,
			TraceData.CollisionChannel,
			CollisionParams
		);

		if ( TraceData.bShowDebugLine )
		{
			DrawDebugHitTrace( World, HitResult, TraceData.DebugLineStart );
		}
	}

	return HitResult;
}

FText RFPSUtils::GetTextFromInt( const int32 Number )
{
	return FText::FromString( FString::FromInt( Number ) );
}

void RFPSUtils::SetAmmoDataTextBlocks( UTextBlock* CurrentAmmo, UTextBlock* MaxAmmo, const FAmmoData AmmoData )
{
	if ( !IsValid( CurrentAmmo ) || !IsValid( MaxAmmo ) )
	{
		return;
	}

	CurrentAmmo->SetText( RFPSUtils::GetTextFromInt( AmmoData.CurrentAmmo ) );
	MaxAmmo->SetText( RFPSUtils::GetTextFromInt( AmmoData.MaxAmmo ) );
}

void RFPSUtils::DrawDebugHitTrace( const UWorld* World, const FHitResult& HitResult, const FVector& LineStart )
{
	if ( !IsValid( World ) )
	{
		return;
	}

	DrawDebugLine(
		World,
		LineStart,
		HitResult.bBlockingHit ? HitResult.ImpactPoint : HitResult.TraceEnd,
		HitResult.bBlockingHit ? FColor::Red : FColor::Green,
		false,
		10.0f,
		0,
		1.0f
	);

	if ( HitResult.bBlockingHit )
	{
		DrawDebugSphere(
			World,
			HitResult.ImpactPoint,
			10.0f,
			8,
			FColor::Red,
			false,
			10.0f,
			0,
			1.0f
		);
	}
}
