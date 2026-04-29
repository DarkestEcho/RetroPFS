// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/RFPSTypes.h"
#include "Weapons/RFPSBaseWeapon.h"
#include "RFPSWeaponComponent.generated.h"

class UChildActorComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RETROFPS_API URFPSWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URFPSWeaponComponent();

protected:
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Ammo" )
	TArray<TSubclassOf<ARFPSBaseWeapon>> Weapons {};

	UPROPERTY( VisibleInstanceOnly, BlueprintReadWrite, Category="Weapon" )
	ARFPSBaseWeapon* CurrentWeapon { nullptr };

public:
	void StartAttack();
	void StopAttack();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	int32 CurrentWeaponIndex { 0 };
};
