// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/RFPSBaseWeapon.h"
#include "PaperFlipbookComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
ARFPSBaseWeapon::ARFPSBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>( TEXT( "SceneRoot" ) );
	SetRootComponent( SceneRoot );

	FireStartPoint = CreateDefaultSubobject<USceneComponent>( TEXT( "FireStartPoint" ) );
	FireStartPoint->SetupAttachment( GetRootComponent() );

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>( "ArrowComponent" );
	ArrowComponent->SetupAttachment( GetRootComponent() );

	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>( TEXT( "FlipbookComponent" ) );
	FlipbookComponent->SetupAttachment( GetRootComponent() );
	FlipbookComponent->SetRelativeRotation( FRotator( 0.0, 90.0, 0.0 ) );
}

// Called when the game starts or when spawned
void ARFPSBaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	FlipbookComponent->SetFlipbook( FlipbookIdle );
}
