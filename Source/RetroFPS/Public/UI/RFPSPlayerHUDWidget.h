// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/RFPSTypes.h"
#include "RFPSPlayerHUDWidget.generated.h"


class URFPSStatusBarWidget;

UCLASS()
class RETROFPS_API URFPSPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Status", meta=( BindWidget ) )
	URFPSStatusBarWidget* StatusBar;

	virtual void NativeOnInitialized() override;

private:
	void UpdateAllAmmoData() const;
	
	void OnAmmoChanged( EAmmoType AmmoType, FAmmoData AmmoData );
	void OnNewPawn( APawn* Pawn );
};
