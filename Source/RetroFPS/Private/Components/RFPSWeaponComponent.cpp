// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RFPSWeaponComponent.h"
#include "Characters/RFPSCharacter.h"
#include "Components/ChildActorComponent.h"

// Sets default values for this component's properties
URFPSWeaponComponent::URFPSWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void URFPSWeaponComponent::StartAttack()
{
	if ( !CurrentWeapon )
	{
		return;
	}

	CurrentWeapon->StartAttack();
}

void URFPSWeaponComponent::StopAttack()
{
	if ( !CurrentWeapon )
	{
		return;
	}

	CurrentWeapon->StopAttack();
}

void URFPSWeaponComponent::AddWeapon( const TSubclassOf<ARFPSBaseWeapon> Weapon )
{
	if (Weapons.Contains( Weapon ))
	{
		return;
	}
	
	Weapons.Add( Weapon );
	SpawnWeapon( Weapons.Num() - 1 );
}

// Called when the game starts
void URFPSWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	if ( Weapons.IsEmpty() )
	{
		return;
	}

	SpawnWeapon( CurrentWeaponIndex );
}

void URFPSWeaponComponent::SpawnWeapon( const int32 WeaponIndex )
{
	DestroyCurrentWeapon();
	if ( ARFPSCharacter* Character = Cast<ARFPSCharacter>( GetOwner() ); IsValid( Character ) )
	{
		FActorSpawnParameters SpawnParameters { FActorSpawnParameters() };
		SpawnParameters.Owner = Character;
		if ( ARFPSBaseWeapon* Weapon = GetWorld()->SpawnActor<ARFPSBaseWeapon>( Weapons[WeaponIndex], SpawnParameters ); IsValid( Weapon ) )
		{
			Weapon->AttachToComponent( Character->GetWeaponSocket(), FAttachmentTransformRules::SnapToTargetIncludingScale );
			CurrentWeapon = Weapon;
		}
	}
}

void URFPSWeaponComponent::DestroyCurrentWeapon()
{
	if ( IsValid( CurrentWeapon ) )
	{
		CurrentWeapon->Destroy();
	}

	CurrentWeapon = nullptr;
}
