// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/RFPSRangedWeapon.h"
#include "Utils/RFPSUtils.h"

// Sets default values
ARFPSRangedWeapon::ARFPSRangedWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ARFPSRangedWeapon::BeginPlay()
{
	Super::BeginPlay();

	check( FireStartPoint );

	if ( GetOwner() )
	{
		AmmoComponentPtr = RFPSUtils::GetComponentFromActor<URFPSAmmoComponent>( GetOwner() );
	}
}

void ARFPSRangedWeapon::MakeShot()
{
	if ( TryDecreaseAmmo() )
	{
		if ( !bFireAfterAnimation )
		{
			MakeAllHits();
		}
		AnimateShot( false );
	}
}

void ARFPSRangedWeapon::MakeAllHits()
{
	for ( int32 Index = 0; Index < ShotsPerAttack; ++Index )
	{
		MakeHit();
	}
}

bool ARFPSRangedWeapon::TryDecreaseAmmo() const
{
	if ( AmmoComponentPtr.IsValid() && AmmoComponentPtr->HasAmmo( AmmoType, AmmoPerAttack ) )
	{
		AmmoComponentPtr->DecreaseAmmo( AmmoType, AmmoPerAttack );
		return true;
	}
	return false;
}

void ARFPSRangedWeapon::OnFireAnimationFinished()
{
	Super::OnFireAnimationFinished();

	if ( bFireAfterAnimation )
	{
		MakeAllHits();
	}
}
