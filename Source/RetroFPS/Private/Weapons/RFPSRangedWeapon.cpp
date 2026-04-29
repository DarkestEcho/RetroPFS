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
	Super::StartAttack();
	MakeShot();
}

void ARFPSRangedWeapon::MakeShot()
{
	if ( bInUse )
	{
		return;
	}

	if ( !AmmoComponentPtr.IsValid() || !AmmoComponentPtr->HasAmmo( AmmoType ) )
	{
		return;
	}
	AmmoComponentPtr->DecreaseAmmo( AmmoType );

	for ( int32 Index = 0; Index < ShotsPerAttack; ++Index )
	{
		MakeHit();
	}

	AnimateShot();

	bInUse = true;
}


void ARFPSRangedWeapon::UpdateFlipbook( UPaperFlipbook* NewFlipbook, bool bLoop )
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

void ARFPSRangedWeapon::OnFireAnimationFinished()
{
	UpdateFlipbook( FlipbookIdle, true );
	bInUse = false;
}

void ARFPSRangedWeapon::AnimateShot()
{
	UpdateFlipbook( FlipbookFire, false );
	if ( FlipbookComponent )
	{
		FlipbookComponent->OnFinishedPlaying.AddDynamic( this, &ARFPSRangedWeapon::OnFireAnimationFinished );
	}
}
