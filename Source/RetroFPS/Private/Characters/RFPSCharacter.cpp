// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/RFPSCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RetroFPS.h"
#include "Components/RFPSWeaponComponent.h"

ARFPSCharacter::ARFPSCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize( 55.f, 96.0f );

	// Create the Camera Component	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>( TEXT( "First Person Camera" ) );
	FirstPersonCameraComponent->SetupAttachment( GetRootComponent() );
	FirstPersonCameraComponent->SetRelativeLocationAndRotation( FVector( -2.8f, 5.89f, 0.0f ), FRotator( 0.0f, 90.0f, -90.0f ) );
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
	FirstPersonCameraComponent->bEnableFirstPersonScale = true;
	FirstPersonCameraComponent->FirstPersonFieldOfView = 70.0f;
	FirstPersonCameraComponent->FirstPersonScale = 0.6f;

	WeaponSceneComponent = CreateDefaultSubobject<USceneComponent>( TEXT( "WeaponSceneComponent" ) );
	WeaponSceneComponent->SetupAttachment( FirstPersonCameraComponent );
	WeaponSceneComponent->SetRelativeScale3D( FVector( 0.07 ) );
	WeaponSceneComponent->SetRelativeLocation( FVector( 20.0, 0.0, -6.0 ) );

	WeaponComponent = CreateDefaultSubobject<URFPSWeaponComponent>( TEXT( "WeaponComponent" ) );

	// configure the character comps
	GetMesh()->SetOwnerNoSee( true );
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

	GetCapsuleComponent()->SetCapsuleSize( 34.0f, 96.0f );

	// Configure character movement
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->AirControl = 0.5f;
}

void ARFPSCharacter::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	// Set up action bindings
	if ( UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>( PlayerInputComponent ) )
	{
		// Jumping
		EnhancedInputComponent->BindAction( JumpAction, ETriggerEvent::Started, this, &ARFPSCharacter::DoJumpStart );
		EnhancedInputComponent->BindAction( JumpAction, ETriggerEvent::Completed, this, &ARFPSCharacter::DoJumpEnd );

		// Moving
		EnhancedInputComponent->BindAction( MoveAction, ETriggerEvent::Triggered, this, &ARFPSCharacter::MoveInput );

		// Looking/Aiming
		EnhancedInputComponent->BindAction( LookAction, ETriggerEvent::Triggered, this, &ARFPSCharacter::LookInput );
		EnhancedInputComponent->BindAction( MouseLookAction, ETriggerEvent::Triggered, this, &ARFPSCharacter::LookInput );
	}
	else
	{
		UE_LOG( LogRetroFPS, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this) );
	}
}


void ARFPSCharacter::MoveInput( const FInputActionValue& Value )
{
	// get the Vector2D move axis
	FVector2D MovementVector = Value.Get<FVector2D>();

	// pass the axis values to the move input
	DoMove( MovementVector.X, MovementVector.Y );
}

void ARFPSCharacter::LookInput( const FInputActionValue& Value )
{
	// get the Vector2D look axis
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// pass the axis values to the aim input
	DoAim( LookAxisVector.X, LookAxisVector.Y );
}

void ARFPSCharacter::DoAim( float Yaw, float Pitch )
{
	if ( GetController() )
	{
		// pass the rotation inputs
		AddControllerYawInput( Yaw );
		AddControllerPitchInput( Pitch );
	}
}

void ARFPSCharacter::DoMove( float Right, float Forward )
{
	if ( GetController() )
	{
		// pass the move inputs
		AddMovementInput( GetActorRightVector(), Right );
		AddMovementInput( GetActorForwardVector(), Forward );
	}
}

void ARFPSCharacter::DoJumpStart()
{
	// pass Jump to the character
	Jump();
}

void ARFPSCharacter::DoJumpEnd()
{
	// pass StopJumping to the character
	StopJumping();
}
