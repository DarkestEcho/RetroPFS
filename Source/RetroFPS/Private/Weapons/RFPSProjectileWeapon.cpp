// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/RFPSProjectileWeapon.h"

#include "Utils/RFPSUtils.h"
#include "Weapons/RFPSProjectile.h"


// Sets default values
ARFPSProjectileWeapon::ARFPSProjectileWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ARFPSProjectileWeapon::MakeHit()
{
	if ( !IsValid( FireStartPoint ) )
	{
		return;
	}

	RFPSUtils::LaunchProjectile( GetWorld(), ProjectileClass, this, FireStartPoint->GetComponentLocation(), FireStartPoint->GetComponentRotation().Vector() );
}
