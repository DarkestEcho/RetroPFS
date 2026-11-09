// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RFPSBaseWeapon.h"
#include "RFPSAutoMeleeWeapon.generated.h"

UCLASS( Abstract, Blueprintable )
class RETROFPS_API ARFPSAutoMeleeWeapon : public ARFPSBaseWeapon
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARFPSAutoMeleeWeapon();

	virtual void StartAttack() override;
	virtual void StopAttack() override;


private:
	FTimerHandle ShotTimerHandle;
};
