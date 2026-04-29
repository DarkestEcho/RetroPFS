// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RFPSAmmoComponent.h"
#include "Types/RFPSConstants.h"

URFPSAmmoComponent::URFPSAmmoComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

FAmmoData URFPSAmmoComponent::GetAmmoData( EAmmoType AmmoType ) const
{
	return AmmoData[static_cast<uint8>( AmmoType )];
}

TMap<EAmmoType, FAmmoData> URFPSAmmoComponent::GetAmmoDataMap() const
{
	TMap<EAmmoType, FAmmoData> AmmoDataMap;
	constexpr uint8 Count = static_cast<uint8>( EAmmoType::Count );
	for ( uint8 Index = 0; Index < Count; Index++ )
	{
		AmmoDataMap.Add( { static_cast<EAmmoType>( Index ), AmmoData[Index] } );
	}
	return MoveTemp( AmmoDataMap );
}

bool URFPSAmmoComponent::HasAmmo( const EAmmoType AmmoType ) const
{
	return GetAmmoData( AmmoType ).CurrentAmmo > 0;
}

bool URFPSAmmoComponent::IsFullAmmo( const EAmmoType AmmoType ) const
{
	return GetAmmoData( AmmoType ).CurrentAmmo == GetAmmoData( AmmoType ).MaxAmmo;
}

void URFPSAmmoComponent::IncreaseAmmo( const EAmmoType AmmoType, const int32 AmmoCount )
{
	SetCurrentAmmo( AmmoType, GetAmmoData( AmmoType ).CurrentAmmo + AmmoCount );
}

void URFPSAmmoComponent::DecreaseAmmo( const EAmmoType AmmoType )
{
	SetCurrentAmmo( AmmoType, GetAmmoData( AmmoType ).CurrentAmmo - GAmmoPerShot );
}

void URFPSAmmoComponent::BeginPlay()
{
	Super::BeginPlay();
}

void URFPSAmmoComponent::SetCurrentAmmo( const EAmmoType AmmoType, int32 Ammo )
{
	Ammo = FMath::Clamp( Ammo, 0, GetAmmoData( AmmoType ).MaxAmmo );
	AmmoData[static_cast<uint8>( AmmoType )].CurrentAmmo = Ammo;

	OnAmmoChanged.Broadcast( AmmoType, GetAmmoData( AmmoType ) );
}


#if WITH_EDITOR
void URFPSAmmoComponent::PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent )
{
	Super::PostEditChangeProperty( PropertyChangedEvent );

	if ( !PropertyChangedEvent.MemberProperty )
	{
		return;
	}

	if ( PropertyChangedEvent.MemberProperty->GetFName() == GET_MEMBER_NAME_CHECKED( URFPSAmmoComponent, AmmoData ) )
	{
		for ( FAmmoData& Data : AmmoData )
		{
			if ( Data.CurrentAmmo > Data.MaxAmmo )
			{
				Data.CurrentAmmo = Data.MaxAmmo;
			}
		}
	}
}
#endif // WITH_EDITOR
