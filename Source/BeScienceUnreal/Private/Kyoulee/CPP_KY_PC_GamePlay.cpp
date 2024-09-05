// Fill out your copyright notice in the Description page of Project Settings.


#include "Kyoulee/CPP_KY_PC_GamePlay.h"

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

void ACPP_KY_PC_GamePlay::EnterVehicle(class APawn* vehicle)
{
	if (IsLocalController())
	{
		ServerPossess(vehicle);
	}
}

void ACPP_KY_PC_GamePlay::ExitVehicle(class APawn* playerCharacter)
{
	if (IsLocalController())
	{
		ServerPossess(playerCharacter);
	}
}

void ACPP_KY_PC_GamePlay::ServerPossess_Implementation(class APawn* possessPawn)
{
	Possess(possessPawn);
}
