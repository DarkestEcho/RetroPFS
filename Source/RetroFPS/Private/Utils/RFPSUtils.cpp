#include "Utils/RFPSUtils.h"

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


FHitResult RFPSUtils::MakeLineTraceSingle( 	const UWorld* World, const FTraceData& TraceData )
{
	FHitResult HitResult {};
	if ( IsValid( World ) )
	{
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActors( TraceData.IgnoredActors );

		const FVector TraceStart { TraceData.ViewPoint.Location };
		const FVector TraceEnd { TraceData.ViewPoint.Location + TraceData.ViewPoint.Rotation.Vector() * TraceData.Distance };

		World->LineTraceSingleByChannel(
			HitResult,
			TraceStart,
			TraceEnd,
			TraceData.CollisionChannel,
			CollisionParams
		);
	}

	return HitResult;
}
