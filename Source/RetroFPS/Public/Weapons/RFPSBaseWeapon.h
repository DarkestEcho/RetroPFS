// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RFPSBaseWeapon.generated.h"

class UPaperFlipbook;
class URFPSWeaponComponent;
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

	virtual void StartAttack();
	virtual void StopAttack();

	bool IsInUse() const;

protected:
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Scene" )
	USceneComponent* SceneRoot;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category="Scene" )
	USceneComponent* FireStartPoint;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Scene" )
	UArrowComponent* ArrowComponent;


	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category="Sprites" )
	UPaperFlipbookComponent* FlipbookComponent;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category="Sprites" )
	UPaperFlipbook* FlipbookIdle;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category="Sprites" )
	UPaperFlipbook* FlipbookFire;


	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = "Specs", meta=( UIMin = "0", UIMax = "100" ) )
	float AttackSpeed { 1.0f };

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = "Specs" )
	float Distance { 0.0f };

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category="Specs", meta=( ClampMin=0 ) )
	float SpreadAngleHorizontal { 0.0f };

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category="Specs", meta=( ClampMin=0 ) )
	float SpreadAngleVertical { 0.0f };

	bool bInUse { false };


	virtual void BeginPlay() override;

	virtual void MakeHit();

#if WITH_EDITOR
	virtual void PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent ) override;
#endif // WITH_EDITOR
};
