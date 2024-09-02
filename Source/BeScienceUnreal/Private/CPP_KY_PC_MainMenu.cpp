// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_KY_PC_MainMenu.h"
#include "CPP_KY_WG_MainMenu.h"


void ACPP_KY_PC_MainMenu::BeginPlay ()
{
	Super::BeginPlay ();

	if (this->WBP_MainMenu_Class)
	{
		this->WBP_MainMenu = CreateWidget<UCPP_KY_WG_MainMenu> (this, this->WBP_MainMenu_Class);
		this->WBP_MainMenu->AddToViewport ();
	}
}
