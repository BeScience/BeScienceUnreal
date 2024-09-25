// Fill out your copyright notice in the Description page of Project Settings.


#include "Kyoulee/CPP_KY_GS_GamePlay.h"
#include "Net/UnrealNetwork.h"

void ACPP_KY_GS_GamePlay::SetGamePlayState(EGamePlayState NewGamePlayState)
{

}

void ACPP_KY_GS_GamePlay::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACPP_KY_GS_GamePlay, GamePlayState);
}
