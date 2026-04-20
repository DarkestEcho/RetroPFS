// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RFPSHUD.generated.h"

/**
 * 
 */
UCLASS()
class RETROFPS_API ARFPSHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

protected:
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Debug" )
	bool bDebugCrosshairEnabled { false };

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Debug" )
	FLinearColor DebugCrosshairColor { FLinearColor::Green };

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Debug" )
	float DebugCrosshairLineSize { 10.0f };

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Debug" )
	float DebugCrosshairThickness { 2.0f };

private:
	void DrawDebugCrosshair();
};
