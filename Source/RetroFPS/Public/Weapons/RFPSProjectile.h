// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RFPSProjectile.generated.h"

class UPaperFlipbook;
class UArrowComponent;
class USphereComponent;
class UPaperFlipbookComponent;
class UProjectileMovementComponent;

UCLASS( Abstract, Blueprintable )
class RETROFPS_API ARFPSProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARFPSProjectile();

	void SetDirection( FVector Direction );
	void ShowDebugSphere( const bool bShow );

protected:
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = Projectile )
	UArrowComponent* ArrowComponent;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = Projectile )
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = Sprite )
	UPaperFlipbookComponent* FlipbookComponent;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = Sprite )
	UPaperFlipbook* FlipbookFly;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = Sprite )
	UPaperFlipbook* FlipbookExplosion;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = Collision )
	USphereComponent* CollisionComponent;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = Projectile )
	float Speed { 0.0f };

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = Projectile )
	float LifeTimeInSeconds { 0.0f };

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = Damage )
	float Damage { 0.0f };

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = Damage )
	bool bRadialDamage { false };

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = Damage, meta=(EditCondition = "bRadialDamage") )
	float DamageRadius { 0.0f };

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = Damage, meta=(EditCondition = "bRadialDamage") )
	bool bFullDamage { false };

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = Sprite )
	float SpriteScaleOnHit { 1.0f };

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = Projectile )
	float ProjectileGravityScale { 0.0f };

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FVector ShotDirection { FVector::ZeroVector };

	bool bShowDebugSphere { false };

	UFUNCTION()
	void OnFinishedPlaying();

	UFUNCTION()
	void OnProjectileHit( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

	AController* GetController() const;

public:
#if WITH_EDITOR
	virtual void PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent ) override;
#endif // WITH_EDITOR
};
