// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RFPSWeaponComponent.h"
#include "Characters/RFPSCharacter.h"

// Sets default values for this component's properties
URFPSWeaponComponent::URFPSWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
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
			Weapon->AttachToComponent( Character->GetWeaponSceneComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale );
			CurrentWeapon = Weapon;
		}
	}
}
