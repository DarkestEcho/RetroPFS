// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RFPSBaseWeapon.generated.h"

class UPaperFlipbook;
class UPaperFlipbookComponent;
class USceneComponent;
class UArrowComponent;

UCLASS( Abstract, NotBlueprintable )
class RETROFPS_API ARFPSBaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARFPSBaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Root" )
	USceneComponent* SceneRoot;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category="Fire" )
	USceneComponent* FireStartPoint;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Sprites" )
	UArrowComponent* ArrowComponent;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category="Sprites" )
	UPaperFlipbookComponent* FlipbookComponent;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category="Sprites" )
	UPaperFlipbook* FlipbookIdle;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category="Sprites" )
	UPaperFlipbook* FlipbookFire;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Specs" )
	float Distance { 0.0f };

	bool bFiring { false };

	virtual void MakeShot() PURE_VIRTUAL( ARFPSBaseWeapon::MakeShot, );

public:
	virtual void StartFire() PURE_VIRTUAL( ARFPSBaseWeapon::StartFire, );
	virtual void StopFire() PURE_VIRTUAL( ARFPSBaseWeapon::StopFire, );

	bool GetIsFiring() const;
};
