// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "RFPSCharacter.generated.h"

class URFPSAmmoComponent;
class URFPSWeaponComponent;
class UInputComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN( LogTemplateCharacter, Log, All );

/**
 *  A basic first person character
 */
UCLASS( abstract )
class ARFPSCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	/** First person camera */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Components" )
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category="Components" )
	USceneComponent* WeaponSocket;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category="Components" )
	URFPSWeaponComponent* WeaponComponent;
	
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category="Components" )
	URFPSAmmoComponent* AmmoComponent;

protected:
	/** Jump Input Action */
	UPROPERTY( EditAnywhere, Category ="Input" )
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY( EditAnywhere, Category ="Input" )
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY( EditAnywhere, Category ="Input" )
	class UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY( EditAnywhere, Category ="Input" )
	class UInputAction* MouseLookAction;
	
	/** Mouse Look Input Action */
	UPROPERTY( EditAnywhere, Category ="Input" )
	class UInputAction* FireAction;

public:
	ARFPSCharacter();

protected:
	/** Called from Input Actions for movement input */
	void MoveInput( const FInputActionValue& Value );

	/** Called from Input Actions for looking input */
	void LookInput( const FInputActionValue& Value );

	/** Handles aim inputs from either controls or UI interfaces */
	UFUNCTION( BlueprintCallable, Category="Input" )
	virtual void DoAim( float Yaw, float Pitch );

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION( BlueprintCallable, Category="Input" )
	virtual void DoMove( float Right, float Forward );

	/** Handles jump start inputs from either controls or UI interfaces */
	UFUNCTION( BlueprintCallable, Category="Input" )
	virtual void DoJumpStart();

	/** Handles jump end inputs from either controls or UI interfaces */
	UFUNCTION( BlueprintCallable, Category="Input" )
	virtual void DoJumpEnd();

protected:
	/** Set up input action bindings */
	virtual void SetupPlayerInputComponent( UInputComponent* InputComponent ) override;

public:
	/** Returns first person camera component **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	USceneComponent* GetWeaponSocket() const { return WeaponSocket; }
};
