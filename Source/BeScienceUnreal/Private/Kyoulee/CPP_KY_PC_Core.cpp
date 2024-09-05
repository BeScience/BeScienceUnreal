// Fill out your copyright notice in the Description page of Project Settings.


#include "Kyoulee/CPP_KY_PC_Core.h"
#include "Kyoulee/CPP_KY_WG_GameMenu.h"

#include "Blueprint/WidgetBlueprintLibrary.h"

void ACPP_KY_PC_Core::BeginPlay ()
{
	UWidgetBlueprintLibrary::SetInputMode_GameOnly ( this, false );

	if (this->WBP_GameMenu_Class)
	{
		this->WBP_GameMenu = CreateWidget<UCPP_KY_WG_GameMenu> (this , this->WBP_GameMenu_Class);
		if (this->WBP_GameMenu)
		{
			this->WBP_GameMenu->AddToViewport ();
			this->WBP_GameMenu->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void ACPP_KY_PC_Core::ToggleGameMenu ()
{
	if (this->WBP_GameMenu)
	{
		if (this->WBP_GameMenu->IsVisible ()) {
			this->WBP_GameMenu->SetVisibility ( ESlateVisibility::Collapsed );
		} else {
			this->WBP_GameMenu->SetVisibility ( ESlateVisibility::Visible );
		}
		FucusWidget ( this , this->WBP_GameMenu );
	}
}


void ACPP_KY_PC_Core::FucusWidget ( APlayerController* PlayerController , UUserWidget* TargetWidget )
{
	this->SetShowMouseCursor ( ! this->ShouldShowMouseCursor () );
	if (this->ShouldShowMouseCursor ()) {
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx ( PlayerController , TargetWidget , EMouseLockMode::DoNotLock );
	} else {
		UWidgetBlueprintLibrary::SetInputMode_GameOnly ( PlayerController );
	}
}

