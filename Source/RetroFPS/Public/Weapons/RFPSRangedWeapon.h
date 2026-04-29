// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RFPSBaseWeapon.h"
#include "Components/RFPSAmmoComponent.h"
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

public:
	virtual void StartAttack() override;

protected:
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Specs" )
	EAmmoType AmmoType { EAmmoType::Bullets };

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Specs", meta=( ClampMin=1 ) )
	int32 ShotsPerAttack { 1 };

	UFUNCTION()
	void OnFireAnimationFinished();

	virtual void MakeShot();

private:
	TWeakObjectPtr<URFPSAmmoComponent> AmmoComponentPtr;

	void UpdateFlipbook( UPaperFlipbook* NewFlipbook, bool bLoop );
	void AnimateShot();
};
