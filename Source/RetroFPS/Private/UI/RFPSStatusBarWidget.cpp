// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RFPSStatusBarWidget.h"

#include "Utils/RFPSUtils.h"

void URFPSStatusBarWidget::SetAmmoData( const EAmmoType AmmoType, const FAmmoData AmmoData ) const
{
	if (AmmoType == EAmmoType::Bullets)
	{
		RFPSUtils::SetAmmoDataTextBlocks( BulletsCount, MaxBulletsCount, AmmoData );
	}
	else if (AmmoType == EAmmoType::Shells)
	{
		RFPSUtils::SetAmmoDataTextBlocks( ShellsCount, MaxShellsCount, AmmoData );
	}
	else if (AmmoType == EAmmoType::Rockets)
	{
		RFPSUtils::SetAmmoDataTextBlocks( RocketsCount, MaxRocketsCount, AmmoData );
	}
	else if (AmmoType == EAmmoType::Cells)
	{
		RFPSUtils::SetAmmoDataTextBlocks( CellsCount, MaxCellsCount, AmmoData );
	}
}
