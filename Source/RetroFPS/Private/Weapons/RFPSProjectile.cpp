// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/RFPSProjectile.h"

#include "PaperFlipbookComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ARFPSProjectile::ARFPSProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>( "CollisionComponent" );
	CollisionComponent->SetCollisionEnabled( ECollisionEnabled::QueryOnly );
	CollisionComponent->SetCollisionResponseToAllChannels( ECR_Block );
	CollisionComponent->SetCollisionResponseToChannel( ECollisionChannel::ECC_Pawn, ECR_Overlap );
	SetRootComponent( CollisionComponent );

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>( "ArrowComponent" );
	ArrowComponent->SetupAttachment( RootComponent );

	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>( "FlipbookComponent" );
	FlipbookComponent->SetupAttachment( RootComponent );
	FlipbookComponent->SetRelativeRotation( FRotator( 0.0, 90.0, 0.0 ) );
	FlipbookComponent->OnFinishedPlaying.AddDynamic( this, &ARFPSProjectile::OnFinishedPlaying );
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>( "UProjectileMovementComponent" );
	ProjectileMovementComponent->ProjectileGravityScale = ProjectileGravityScale;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
}

void ARFPSProjectile::SetDirection( const FVector& Direction )
{
	ShotDirection = Direction;
}

void ARFPSProjectile::ShowDebugSphere( const bool bShow )
{
	bShowDebugSphere = bShow;
}

// Called when the game starts or when spawned
void ARFPSProjectile::BeginPlay()
{
	Super::BeginPlay();

	check( ArrowComponent );
	check( FlipbookComponent );
	check( FlipbookFly );
	check( FlipbookExplosion );
	check( ProjectileMovementComponent );

	if ( FlipbookComponent && FlipbookFly )
	{
		SetFlipbook( FlipbookFly );
	}

	ProjectileMovementComponent->InitialSpeed = Speed;
	ProjectileMovementComponent->MaxSpeed = Speed;

	ProjectileMovementComponent->Velocity = ShotDirection * ProjectileMovementComponent->InitialSpeed;

	CollisionComponent->OnComponentHit.AddDynamic( this, &ARFPSProjectile::OnProjectileHit );

	SetLifeSpan( LifeTimeInSeconds );
}

void ARFPSProjectile::OnFinishedPlaying()
{
	Destroy();
}

void ARFPSProjectile::OnProjectileHit( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit )
{
	ProjectileMovementComponent->StopMovementImmediately();

	// Apply Damage

	/*UGameplayStatics::ApplyRadialDamage( GetWorld(),
		Damage,
		GetActorLocation(),
		DamageRadius,
		UDamageType::StaticClass(),
		{},
		this,
		GetController(),
		bFullDamage);
		*/

	SetFlipbook( FlipbookExplosion );
	FlipbookComponent->SetLooping( false );
	FlipbookComponent->SetRelativeScale3D( FlipbookComponent->GetRelativeScale3D() * SpriteScaleOnHit );

	if ( bShowDebugSphere )
	{
		DrawDebugSphere(
			GetWorld(),
			Hit.ImpactPoint,
			DamageRadius,
			8,
			FColor::Yellow,
			false,
			10.0f,
			0,
			2.0f
		);
	}
}

AController* ARFPSProjectile::GetController() const
{
	const APawn* Pawn = Cast<APawn>( GetOwner() );
	return Pawn ? Pawn->GetController() : nullptr;
}

void ARFPSProjectile::SetFlipbook( UPaperFlipbook* Flipbook ) const
{
	FlipbookComponent->SetFlipbook( Flipbook );
	FlipbookComponent->SetCustomPrimitiveDataFloat( 0, SpritePitchAmount );
}

#if WITH_EDITOR
void ARFPSProjectile::PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent )
{
	Super::PostEditChangeProperty( PropertyChangedEvent );

	if ( !PropertyChangedEvent.Property )
	{
		return;
	}

	if ( PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED( ARFPSProjectile, FlipbookFly ) )
	{
		if ( FlipbookComponent )
		{
			SetFlipbook( FlipbookFly );
		}
	}
}

void ARFPSProjectile::OnConstruction( const FTransform& Transform )
{
	Super::OnConstruction( Transform );
	FlipbookComponent->SetCustomPrimitiveDataFloat( 0, SpritePitchAmount );
}


#endif // WITH_EDITOR
