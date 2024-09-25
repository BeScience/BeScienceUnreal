// Fill out your copyright notice in the Description page of Project Settings.


#include "Kyoulee/CPP_KY_PC_GamePlay.h"
#include "Net/UnrealNetwork.h"
#include "UI/QuestWidget.h"
#include "BaseCharacter.h"

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

		if (this->QuestWidget_Class)
		{
			this->QuestWidget = CreateWidget<UQuestWidget>(this, this->QuestWidget_Class);
			this->QuestWidget->AddToViewport();
		}
	}
}

void ACPP_KY_PC_GamePlay::EnterVehicle(class APawn* vehicle)
{
	if (IsLocalController())
	{
		CompleteQuest(2);
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

void ACPP_KY_PC_GamePlay::CompleteQuest(int32 QuestIndex)
{
	if (IsLocalController())
	{
		QuestWidget->CompleteQuest(QuestIndex);
	}

}

void ACPP_KY_PC_GamePlay::ServerPossess_Implementation(class APawn* possessPawn)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("이것은 로그 메시지입니다!"));
	MulticastPossess(possessPawn);
}

void ACPP_KY_PC_GamePlay::MulticastPossess_Implementation(class APawn* possessPawn)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("이것은 로그 메시지입니다!"));
	Possess(possessPawn);
	ABaseCharacter* player = Cast<ABaseCharacter>(possessPawn);
	if (player)
	{
		player->SetHidden(false);
	}
}
