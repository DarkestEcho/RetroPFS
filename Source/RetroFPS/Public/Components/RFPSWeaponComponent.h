// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapons/RFPSBaseWeapon.h"
#include "RFPSWeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RETROFPS_API URFPSWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URFPSWeaponComponent();
	
protected:
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category="Weapon" )
	TSubclassOf<ARFPSBaseWeapon> PistolClass;
	
	UPROPERTY( VisibleInstanceOnly, BlueprintReadOnly, Category="Weapon" )
	ARFPSBaseWeapon* CurrentWeapon;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
