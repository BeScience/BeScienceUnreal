// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_KY_PC_GamePlay.h"

void ACPP_KY_PC_GamePlay::BeginPlay ()
{
	Super::BeginPlay ();

	if (this->IsLocalPlayerController ())
	{
		if (this->WBP_Gameplay_HUD_Class)
		{
			this->WBP_Gameplay_HUD = CreateWidget<UCPP_KY_WG_Gameplay_HUD> ( this , this->WBP_Gameplay_HUD_Class );
			this->WBP_Gameplay_HUD->AddToViewport ();
		}
	}
}
