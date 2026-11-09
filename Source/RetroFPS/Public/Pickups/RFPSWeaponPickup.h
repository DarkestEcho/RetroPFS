// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RFPSBasePickup.h"
#include "RFPSWeaponPickup.generated.h"

class ARFPSBaseWeapon;
enum class EWeaponType : uint8;

UCLASS( Blueprintable )
class RETROFPS_API ARFPSWeaponPickup : public ARFPSBasePickup
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARFPSWeaponPickup();

protected:
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category=Weapon )
	TSubclassOf<ARFPSBaseWeapon> WeaponClass;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnCollisionOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult ) override;
};
