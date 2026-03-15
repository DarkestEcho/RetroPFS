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
		if ( ARFPSBaseWeapon* Pistol = GetWorld()->SpawnActor<ARFPSBaseWeapon>( PistolClass ) )
		{
			Pistol->SetOwner( Character );
			Pistol->AttachToComponent( Character->GetWeaponSceneComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale );
			CurrentWeapon = Pistol;
		}
	}
}
