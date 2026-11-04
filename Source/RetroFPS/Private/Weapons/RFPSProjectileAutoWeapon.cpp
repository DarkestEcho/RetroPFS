// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/RFPSProjectileAutoWeapon.h"

#include "Utils/RFPSUtils.h"


// Sets default values
ARFPSProjectileAutoWeapon::ARFPSProjectileAutoWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ARFPSProjectileAutoWeapon::MakeHit()
{
	if ( !IsValid( FireStartPoint ) )
	{
		return;
	}

	RFPSUtils::LaunchProjectile( GetWorld(), ProjectileClass, this, FireStartPoint->GetComponentLocation(), FireStartPoint->GetComponentRotation().Vector() );
}
