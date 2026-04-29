// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RFPSPlayerHUDWidget.h"

#include "Components/RFPSAmmoComponent.h"
#include "UI/RFPSStatusBarWidget.h"
#include "Utils/RFPSUtils.h"

void URFPSPlayerHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if ( GetOwningPlayer() )
	{
		GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject( this, &URFPSPlayerHUDWidget::OnNewPawn );
		OnNewPawn( GetOwningPlayerPawn() );
	}
}

void URFPSPlayerHUDWidget::UpdateAllAmmoData() const
{
	const URFPSAmmoComponent* AmmoComponent = RFPSUtils::GetComponentFromActor<URFPSAmmoComponent>( GetOwningPlayerPawn() );
	if ( !IsValid( AmmoComponent ) )
	{
		return;
	}

	TMap<EAmmoType, FAmmoData> AmmoDataMap = AmmoComponent->GetAmmoDataMap();
	for ( const auto& [Key, Value] : AmmoDataMap )
	{
		StatusBar->SetAmmoData( Key, Value );
	}
}

void URFPSPlayerHUDWidget::OnAmmoChanged( EAmmoType AmmoType, FAmmoData AmmoData )
{
	StatusBar->SetAmmoData( AmmoType, AmmoData );
}

void URFPSPlayerHUDWidget::OnNewPawn( APawn* Pawn )
{
	URFPSAmmoComponent* AmmoComponent = RFPSUtils::GetComponentFromActor<URFPSAmmoComponent>( Pawn );

	if ( AmmoComponent && !AmmoComponent->OnAmmoChanged.IsBoundToObject( this ) )
	{
		AmmoComponent->OnAmmoChanged.AddUObject( this, &URFPSPlayerHUDWidget::OnAmmoChanged );
	}

	UpdateAllAmmoData();
}
