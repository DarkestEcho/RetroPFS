#pragma once
#include "Types/RFPSTypes.h"

class ACharacter;

class RFPSUtils
{
public:
	static FViewPoint GetPawnViewPoint( const APawn* Pawn );
	static FHitResult MakeLineTraceSingle( const UWorld* World, const FTraceData& TraceData );
};
