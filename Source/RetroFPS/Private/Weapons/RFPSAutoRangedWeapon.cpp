// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/RFPSAutoRangedWeapon.h"

#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"

void ARFPSAutoRangedWeapon::StartAttack()
{
	if ( !HasAmmo() || !FlipbookFire )
	{
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(
		ShotTimerHandle,
		this,
		&ARFPSAutoRangedWeapon::MakeShot,
		FlipbookFire->GetTotalDuration(),
		true,
		0.0f
	);

	AnimateShot( true );
}

void ARFPSAutoRangedWeapon::StopAttack()
{
	GetWorld()->GetTimerManager().ClearTimer( ShotTimerHandle );
	FlipbookComponent->SetLooping( false );
}

void ARFPSAutoRangedWeapon::MakeShot()
{
	if ( !TryDecreaseAmmo() )
	{
		StopAttack();
		return;
	}
	MakeAllHits();
}

void ARFPSAutoRangedWeapon::OnFireAnimationFinished()
{
	UpdateFlipbook( FlipbookIdle, true );
}

bool ARFPSAutoRangedWeapon::HasAmmo() const
{
	return AmmoComponentPtr.IsValid() && AmmoComponentPtr->HasAmmo( AmmoType );
}
