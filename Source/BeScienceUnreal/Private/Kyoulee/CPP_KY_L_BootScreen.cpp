// Fill out your copyright notice in the Description page of Project Settings.


#include "Kyoulee/CPP_KY_L_BootScreen.h"
#include "Kyoulee/CPP_KY_WG_BootScreen.h"
#include <Kismet/GameplayStatics.h>
#include <Blueprint/WidgetBlueprintLibrary.h>

void ACPP_KY_L_BootScreen::BeginPlay ()
{
	if (this->WBP_BootScreen_Class)
	{
		this->WBP_BootScreen = CreateWidget<UCPP_KY_WG_BootScreen>( this->GetWorld() , this->WBP_BootScreen_Class);
		this->WBP_BootScreen->AddToViewport ();
	}
	UWidgetBlueprintLibrary::SetInputMode_GameOnly ( UGameplayStatics::GetPlayerController ( this->GetWorld() , 0));
}
