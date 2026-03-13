// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/RFPSPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "Camera/RFPSPlayerCameraManager.h"

ARFPSPlayerController::ARFPSPlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = ARFPSPlayerCameraManager::StaticClass();
}


void ARFPSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Context
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}
		}
	}
	
}