// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RFPSBasePickup.generated.h"

class UPaperSpriteComponent;
class UPaperSprite;
class UArrowComponent;
class USphereComponent;

UCLASS( Abstract, NotBlueprintable )
class RETROFPS_API ARFPSBasePickup : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARFPSBasePickup();

protected:
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Components" )
	USphereComponent* CollisionComponent;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Components" )
	UArrowComponent* ArrowComponent;
	
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Components" )
	UPaperSpriteComponent* SpriteComponent;
	
	UFUNCTION()
	virtual void OnCollisionOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult );
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
