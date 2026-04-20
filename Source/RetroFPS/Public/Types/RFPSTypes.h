#pragma once

//#include "RFPSTypes.generated.h"

class UWorld;

struct FViewPoint
{
	FVector Location{ FVector::ZeroVector };
	FRotator Rotation{ FRotator::ZeroRotator };
};

struct FTraceData
{
	FViewPoint ViewPoint;
	float Distance;
	ECollisionChannel CollisionChannel;
	TArray<const AActor*> IgnoredActors;
};
