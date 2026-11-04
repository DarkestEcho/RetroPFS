// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RFPSAutoRangedWeapon.h"
#include "RFPSProjectileAutoWeapon.generated.h"

class ARFPSProjectile;

UCLASS( Abstract, Blueprintable )
class RETROFPS_API ARFPSProjectileAutoWeapon : public ARFPSAutoRangedWeapon
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARFPSProjectileAutoWeapon();

protected:
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = Projectile )
	TSubclassOf<ARFPSProjectile> ProjectileClass;
	
	virtual void MakeHit() override;
};
