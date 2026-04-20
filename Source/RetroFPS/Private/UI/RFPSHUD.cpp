// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RFPSHUD.h"

#include "Engine/Canvas.h"

void ARFPSHUD::DrawHUD()
{
	Super::DrawHUD();

	if ( bDebugCrosshairEnabled )
	{
		DrawDebugCrosshair();
	}
}

void ARFPSHUD::DrawDebugCrosshair()
{
	if ( !IsValid( Canvas ) )
	{
		return;
	}

	const FVector2f Center( Canvas->SizeX * 0.5, Canvas->SizeY * 0.5 );
	const float HalfLineSize = DebugCrosshairLineSize / 2.0f;
	const FLinearColor LinearColor = DebugCrosshairColor;

	DrawLine( Center.X - HalfLineSize, Center.Y, Center.X + HalfLineSize, Center.Y, LinearColor, DebugCrosshairThickness );
	DrawLine( Center.X, Center.Y - HalfLineSize, Center.X, Center.Y + HalfLineSize, LinearColor, DebugCrosshairThickness );
}
