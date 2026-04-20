// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RFPSWeaponComponent.h"
#include "Characters/RFPSCharacter.h"
#include "Components/ChildActorComponent.h"

// Sets default values for this component's properties
URFPSWeaponComponent::URFPSWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void URFPSWeaponComponent::StartFire()
{
	if ( !CurrentWeapon )
	{
		return;
	}
	CurrentWeapon->StartFire();
}

void URFPSWeaponComponent::StopFire()
{
	if ( !CurrentWeapon )
	{
		return;
	}
	CurrentWeapon->StopFire();
}

// Called when the game starts
void URFPSWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	if ( ARFPSCharacter* Character = Cast<ARFPSCharacter>( GetOwner() ) )
	{
		if ( ARFPSBaseWeapon* Weapon = GetWorld()->SpawnActor<ARFPSBaseWeapon>( WeaponClass ) )
		{
			Weapon->SetOwner( Character );
			
			Weapon->AttachToComponent( Character->GetWeaponSocket(), FAttachmentTransformRules::SnapToTargetIncludingScale );
			CurrentWeapon = Weapon;
		}
	}
}
