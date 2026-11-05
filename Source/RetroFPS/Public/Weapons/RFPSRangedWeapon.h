// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RFPSBaseWeapon.h"
#include "Components/RFPSAmmoComponent.h"
#include "Types/RFPSConstants.h"
#include "RFPSRangedWeapon.generated.h"

class UPaperFlipbook;

UCLASS( Abstract, Blueprintable )
class RETROFPS_API ARFPSRangedWeapon : public ARFPSBaseWeapon
{
	GENERATED_BODY()

public:
	ARFPSRangedWeapon();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Specs" )
	EAmmoType AmmoType { EAmmoType::Bullets };

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Specs", meta=( ClampMin=1 ) )
	int32 ShotsPerAttack { 1 };

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Specs", meta=( ClampMin=1 ) )
	int32 AmmoPerAttack { GAmmoPerShot };

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = Projectile )
	bool bFireAfterAnimation { false };

	virtual void MakeShot() override;

	void MakeAllHits();

	bool TryDecreaseAmmo() const;
	
	virtual void OnFireAnimationFinished() override;

	TWeakObjectPtr<URFPSAmmoComponent> AmmoComponentPtr;
};
