// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/RFPSConstants.h"
#include "Types/RFPSTypes.h"
#include "RFPSAmmoComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RETROFPS_API URFPSAmmoComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	URFPSAmmoComponent();

	FAmmoData GetAmmoData( EAmmoType AmmoType ) const;
	TMap<EAmmoType, FAmmoData> GetAmmoDataMap() const;

	bool HasAmmo( const EAmmoType AmmoType, const int32 AmmoPerShot = GAmmoPerShot ) const;
	bool IsFullAmmo( const EAmmoType AmmoType ) const;

	void IncreaseAmmo( const EAmmoType AmmoType, const int32 AmmoCount = GAmmoPerShot );
	void DecreaseAmmo( const EAmmoType AmmoType, const int32 AmmoCount = GAmmoPerShot );
	
	FOnAmmoChangedSignature OnAmmoChanged;

protected:
	UPROPERTY( EditDefaultsOnly, Category="Ammo", meta = (ArraySizeEnum = "AmmoType") )
	FAmmoData AmmoData[static_cast<uint8>( EAmmoType::Count )];

#if WITH_EDITOR
	virtual void PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent ) override;
#endif // WITH_EDITOR

private:
	void SetCurrentAmmo( const EAmmoType AmmoType, int32 Ammo );
};
