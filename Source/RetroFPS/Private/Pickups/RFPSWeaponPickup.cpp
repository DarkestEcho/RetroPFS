// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/RFPSWeaponPickup.h"

#include "Characters/RFPSCharacter.h"
#include "Components/RFPSWeaponComponent.h"
#include "Utils/RFPSUtils.h"


// Sets default values
ARFPSWeaponPickup::ARFPSWeaponPickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ARFPSWeaponPickup::BeginPlay()
{
	Super::BeginPlay();
}

void ARFPSWeaponPickup::OnCollisionOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult )
{
	if ( const ARFPSCharacter* Player = Cast<ARFPSCharacter>( OtherActor ); IsValid( Player ) )
	{
		if ( URFPSWeaponComponent* WeaponComponent = RFPSUtils::GetComponentFromActor<URFPSWeaponComponent>( Player ); IsValid( WeaponComponent ) )
		{
			WeaponComponent->AddWeapon( WeaponClass );
		}
	}

	Destroy();
}
