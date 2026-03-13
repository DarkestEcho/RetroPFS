// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "GameFramework/PlayerController.h"
#include "RFPSPlayerController.generated.h"


UCLASS( abstract, config="Game" )
class RETROFPS_API ARFPSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/** Constructor */
	ARFPSPlayerController();

protected:
	/** Input Mapping Contexts */
	UPROPERTY( EditAnywhere, Category="Input|Input Mappings" )
	TArray<UInputMappingContext*> DefaultMappingContexts;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;
};
