// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RFPSBaseWeapon.generated.h"

class UPaperFlipbookComponent;
class USceneComponent;
class UArrowComponent;

UCLASS( Abstract, Blueprintable )
class RETROFPS_API ARFPSBaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARFPSBaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category="Sprites" )
	USceneComponent* SceneRoot;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Sprites" )
	UArrowComponent* ArrowComponent;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category="Sprites" )
	UPaperFlipbookComponent* FlipbookComponent;
};
