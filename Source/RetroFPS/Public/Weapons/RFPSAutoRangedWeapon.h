// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/RFPSRangedWeapon.h"
#include "RFPSAutoRangedWeapon.generated.h"

/**
 * 
 */
UCLASS( Abstract, Blueprintable )
class RETROFPS_API ARFPSAutoRangedWeapon : public ARFPSRangedWeapon
{
	GENERATED_BODY()

public:
	virtual void StartAttack() override;
	virtual void StopAttack() override;

protected:
	virtual void MakeShot() override;

	virtual void OnFireAnimationFinished() override;

private:
	FTimerHandle ShotTimerHandle;
	bool HasAmmo() const;
};
