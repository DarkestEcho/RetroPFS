// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RFPSRangedWeapon.h"
#include "RFPSProjectileWeapon.generated.h"

class ARFPSProjectile;

UCLASS( Abstract, Blueprintable )
class RETROFPS_API ARFPSProjectileWeapon : public ARFPSRangedWeapon
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARFPSProjectileWeapon();

protected:
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = Projectile )
	TSubclassOf<ARFPSProjectile> ProjectileClass;
	
	virtual void MakeHit() override;
};
