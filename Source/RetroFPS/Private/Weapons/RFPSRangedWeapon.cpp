// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/RFPSRangedWeapon.h"
#include "Utils/RFPSUtils.h"
#include "Types/RFPSTypes.h"

#include "PaperFlipbookComponent.h"


// Sets default values
ARFPSRangedWeapon::ARFPSRangedWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	FireStartPoint = CreateDefaultSubobject<USceneComponent>( TEXT( "FireStartPoint" ) );
	FireStartPoint->SetupAttachment( GetRootComponent() );
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

void ARFPSRangedWeapon::StartAttack()
{
	if ( bInUse )
	{
		return;
	}
	bInUse = true;
	MakeShot();
}

void ARFPSRangedWeapon::MakeShot()
{
	if ( TryDecreaseAmmo() )
	{
		MakeAllHits();
		AnimateShot( false );
	}
}

void ARFPSRangedWeapon::UpdateFlipbook( UPaperFlipbook* NewFlipbook, const bool bLoop ) const
{
	if ( !NewFlipbook || !FlipbookComponent )
	{
		return;
	}
	FlipbookComponent->SetFlipbook( NewFlipbook );
	FlipbookComponent->SetLooping( bLoop );
	FlipbookComponent->PlayFromStart();
	FlipbookComponent->OnFinishedPlaying.Clear();
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
	if ( AmmoComponentPtr.IsValid() && AmmoComponentPtr->HasAmmo( AmmoType ) )
	{
		AmmoComponentPtr->DecreaseAmmo( AmmoType );
		return true;
	}
	return false;
}

void ARFPSRangedWeapon::OnFireAnimationFinished()
{
	UpdateFlipbook( FlipbookIdle, true );
	bInUse = false;
}

void ARFPSRangedWeapon::AnimateShot( const bool bLoop )
{
	UpdateFlipbook( FlipbookFire, bLoop );
	if ( FlipbookComponent )
	{
		FlipbookComponent->OnFinishedPlaying.AddDynamic( this, &ARFPSRangedWeapon::OnFireAnimationFinished );
	}
}
