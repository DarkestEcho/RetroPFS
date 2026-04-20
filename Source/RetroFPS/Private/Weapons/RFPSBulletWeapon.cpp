// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/RFPSBulletWeapon.h"
#include "Utils/RFPSUtils.h"
#include "Types/RFPSTypes.h"

#include "PaperFlipbookComponent.h"


// Sets default values
ARFPSBulletWeapon::ARFPSBulletWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ARFPSBulletWeapon::BeginPlay()
{
	Super::BeginPlay();
}


void ARFPSBulletWeapon::StartFire()
{
	if ( bFiring )
	{
		return;
	}

	const FHitResult HitResult = RFPSUtils::MakeLineTraceSingle(
		GetWorld(),
		{
			RFPSUtils::GetPawnViewPoint( Cast<APawn>( GetOwner() ) ),
			Distance,
			ECC_Visibility,
			{ this, GetOwner() }
		}
	);

	DrawDebugLine(
		GetWorld(),
		FireStartPoint->GetComponentLocation(),
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
			GetWorld(),
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

	FlipbookComponent->SetFlipbook( FlipbookFire );
	FlipbookComponent->SetLooping( false );
	FlipbookComponent->PlayFromStart();
	FlipbookComponent->OnFinishedPlaying.Clear();
	FlipbookComponent->OnFinishedPlaying.AddDynamic( this, &ARFPSBulletWeapon::OnFireAnimationFinished );

	bFiring = true;

	// TODO+: Prepare Data For Trace
	// TODO+: Make Trace
	// TODO+: Check Trace Result
	// TODO: Apply Damage
}

void ARFPSBulletWeapon::StopFire()
{
}

void ARFPSBulletWeapon::OnFireAnimationFinished()
{
	FlipbookComponent->SetFlipbook( FlipbookIdle );
	FlipbookComponent->PlayFromStart();
	FlipbookComponent->OnFinishedPlaying.Clear();
	bFiring = false;
}
