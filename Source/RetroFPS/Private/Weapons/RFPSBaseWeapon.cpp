// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/RFPSBaseWeapon.h"

#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "Components/ArrowComponent.h"
#include "Utils/RFPSUtils.h"

// Sets default values
ARFPSBaseWeapon::ARFPSBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>( TEXT( "SceneRoot" ) );
	SetRootComponent( SceneRoot );

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>( "ArrowComponent" );
	ArrowComponent->SetupAttachment( GetRootComponent() );

	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>( TEXT( "FlipbookComponent" ) );
	FlipbookComponent->SetupAttachment( GetRootComponent() );
	FlipbookComponent->SetRelativeRotation( FRotator( 0.0, 90.0, 0.0 ) );
	
	FlipbookComponent->SetCollisionEnabled( ECollisionEnabled::NoCollision );
	FlipbookComponent->SetGenerateOverlapEvents( false );
	
	FireStartPoint = CreateDefaultSubobject<USceneComponent>( TEXT( "FireStartPoint" ) );
	FireStartPoint->SetupAttachment( GetRootComponent() );
}

void ARFPSBaseWeapon::MakeHit()
{
	if ( !IsValid( FireStartPoint ) )
	{
		return;
	}

	const FHitResult HitResult = GetHitResult();
	// Apply Damage()
}

FHitResult ARFPSBaseWeapon::GetHitResult()
{
	return RFPSUtils::MakeLineTraceSingle(
		GetWorld(),
		{
			RFPSUtils::GetPawnViewPoint( Cast<APawn>( GetOwner() ) ),
			Distance,
			SpreadAngle,
			{ this, GetOwner() },
			ECC_Visibility,
			bShowTraces,
			FireStartPoint->GetComponentLocation(),
		}
	);
}

void ARFPSBaseWeapon::UpdateFlipbook( UPaperFlipbook* NewFlipbook, const bool bLoop ) const
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

void ARFPSBaseWeapon::AnimateShot( const bool bLoop )
{
	UpdateFlipbook( FlipbookFire, bLoop );
	if ( FlipbookComponent )
	{
		FlipbookComponent->OnFinishedPlaying.AddDynamic( this, &ARFPSBaseWeapon::OnFireAnimationFinished );
	}
}

void ARFPSBaseWeapon::MakeShot()
{
	MakeHit();
	AnimateShot( false );
}

void ARFPSBaseWeapon::OnFireAnimationFinished()
{
	UpdateFlipbook( FlipbookIdle, true );
	bInUse = false;
}

// Called when the game starts or when spawned
void ARFPSBaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	check( FlipbookComponent );
	check( FlipbookFire )
	check( FlipbookIdle )

	if ( FlipbookIdle )
	{
		FlipbookComponent->SetFlipbook( FlipbookIdle );
	}

	if ( FlipbookFire )
	{
		const FScopedFlipbookMutator FlipbookMutator { FlipbookFire };
		FlipbookMutator.FramesPerSecond = AttackSpeed;
	}
}

#if WITH_EDITOR
void ARFPSBaseWeapon::PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent )
{
	Super::PostEditChangeProperty( PropertyChangedEvent );

	if ( !PropertyChangedEvent.Property )
	{
		return;
	}

	if ( PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED( ARFPSBaseWeapon, FlipbookIdle ) )
	{
		if ( FlipbookComponent )
		{
			FlipbookComponent->SetFlipbook( FlipbookIdle );
		}
	}
}
#endif // WITH_EDITOR

void ARFPSBaseWeapon::StartAttack()
{
	if ( bInUse )
	{
		return;
	}
	bInUse = true;
	MakeShot();
}

void ARFPSBaseWeapon::StopAttack()
{
}


bool ARFPSBaseWeapon::IsInUse() const
{
	return bInUse;
}
