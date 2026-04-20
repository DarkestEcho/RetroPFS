// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RFPSBaseWeapon.h"
#include "RFPSBulletWeapon.generated.h"

UCLASS( Blueprintable )
class RETROFPS_API ARFPSBulletWeapon : public ARFPSBaseWeapon
{
	GENERATED_BODY()

public:
	ARFPSBulletWeapon();

protected:
	virtual void BeginPlay() override;

public:
	virtual void StartFire() override;
	virtual void StopFire() override;
	
protected:
	UFUNCTION()
	void OnFireAnimationFinished();
};
