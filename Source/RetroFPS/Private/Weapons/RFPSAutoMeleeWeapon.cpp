// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/RFPSAutoMeleeWeapon.h"

#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"


// Sets default values
ARFPSAutoMeleeWeapon::ARFPSAutoMeleeWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ARFPSAutoMeleeWeapon::StartAttack()
{
	if ( bInUse )
	{
		return;
	}
	if ( !FlipbookFire )
	{
		return;
	}
	bInUse = true;

	GetWorld()->GetTimerManager().SetTimer(
		ShotTimerHandle,
		this,
		&ARFPSAutoMeleeWeapon::MakeShot,
		FlipbookFire->GetTotalDuration(),
		true,
		0.0f
	);

	AnimateShot( true );
}

void ARFPSAutoMeleeWeapon::StopAttack()
{
	GetWorld()->GetTimerManager().ClearTimer( ShotTimerHandle );
	FlipbookComponent->SetLooping( false );
}



