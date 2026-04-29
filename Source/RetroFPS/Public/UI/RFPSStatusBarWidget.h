// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/RFPSTypes.h"
#include "RFPSStatusBarWidget.generated.h"

class UTextBlock;

UCLASS()
class RETROFPS_API URFPSStatusBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetAmmoData( EAmmoType AmmoType, FAmmoData AmmoData ) const;

protected:
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Ammo", meta=( BindWidget ) )
	UTextBlock* BulletsCount;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Ammo", meta=( BindWidget ) )
	UTextBlock* MaxBulletsCount;


	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Ammo", meta=( BindWidget ) )
	UTextBlock* ShellsCount;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Ammo", meta=( BindWidget ) )
	UTextBlock* MaxShellsCount;


	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Ammo", meta=( BindWidget ) )
	UTextBlock* RocketsCount;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Ammo", meta=( BindWidget ) )
	UTextBlock* MaxRocketsCount;


	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Ammo", meta=( BindWidget ) )
	UTextBlock* CellsCount;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category="Ammo", meta=( BindWidget ) )
	UTextBlock* MaxCellsCount;

};
