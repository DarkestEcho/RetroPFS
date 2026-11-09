// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/RFPSBasePickup.h"

#include "PaperSpriteComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"


// Sets default values
ARFPSBasePickup::ARFPSBasePickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>( "CollisionComponent" );
	CollisionComponent->SetupAttachment( RootComponent );
	CollisionComponent->SetCollisionResponseToAllChannels( ECR_Ignore );
	CollisionComponent->SetCollisionResponseToChannel( ECC_Pawn, ECR_Overlap );
	CollisionComponent->SetCollisionObjectType( ECC_GameTraceChannel2 );
	CollisionComponent->SetCollisionEnabled( ECollisionEnabled::QueryAndPhysics );
	CollisionComponent->CanCharacterStepUpOn = ECB_No;
	CollisionComponent->OnComponentBeginOverlap.AddDynamic( this, &ARFPSBasePickup::OnCollisionOverlap );

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>( "ArrowComponent" );
	ArrowComponent->SetupAttachment( CollisionComponent );
	
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>( "SpriteComponent" );
	SpriteComponent->SetupAttachment( CollisionComponent );
	SpriteComponent->SetRelativeRotation( FRotator( 0.0, 90.0, 0.0 ) );
	SpriteComponent->SetCollisionEnabled( ECollisionEnabled::NoCollision );
	SpriteComponent->SetGenerateOverlapEvents( false );
}

void ARFPSBasePickup::OnCollisionOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult )
{
}

// Called when the game starts or when spawned
void ARFPSBasePickup::BeginPlay()
{
	Super::BeginPlay();
}
