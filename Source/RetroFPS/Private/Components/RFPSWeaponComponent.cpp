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

// Called when the game starts
void URFPSWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	if ( Weapons.IsEmpty() )
	{
		return;
	}

	if ( ARFPSCharacter* Character = Cast<ARFPSCharacter>( GetOwner() ) )
	{
		FActorSpawnParameters SpawnParameters { FActorSpawnParameters() };
		SpawnParameters.Owner = Character;
		if ( ARFPSBaseWeapon* Weapon = GetWorld()->SpawnActor<ARFPSBaseWeapon>( Weapons[CurrentWeaponIndex], SpawnParameters ) )
		{
			Weapon->AttachToComponent( Character->GetWeaponSocket(), FAttachmentTransformRules::SnapToTargetIncludingScale );
			CurrentWeapon = Weapon;
		}
	}
}
