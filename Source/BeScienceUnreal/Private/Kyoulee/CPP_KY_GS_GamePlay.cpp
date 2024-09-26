﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Kyoulee/CPP_KY_GS_GamePlay.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/PlayerController.h"
#include "Vehicle/BSU_VehiclePawn.h"

void ACPP_KY_GS_GamePlay::SetGamePlayState(EGamePlayState NewGamePlayState)
{
	GamePlayState = NewGamePlayState;
	
    if (EGamePlayState::EReady == GamePlayState)
    {
        // 3초 후 실제 게임 시작
        if (HasAuthority())
        {
            GetWorldTimerManager().SetTimer(GameStartTimer, this, &ACPP_KY_GS_GamePlay::StartGame, 3.0f, false);
            MulticastReadyGame();
        }
    }
    // EReady 상태 3초 후 실행
	else if (EGamePlayState::EPlaying == GamePlayState)
	{
		// 차량을 출발 시킨다.
        if (HasAuthority())
        {
            MulticastStartGame();
        }
	}
    else if (EGamePlayState::EGameOver == GamePlayState)
    {
		// 게임 종료
		if (HasAuthority())
		{
			MulticastEndGame();
            GamePlayState = EGamePlayState::EWaiting;
		}
    }
}

void ACPP_KY_GS_GamePlay::OnRep_GameElapsedTime()
{
    // 컨트롤러의 폰을 가져온다.
	APlayerController* PlayerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController)
	{
        ABSU_VehiclePawn* Vehicle = Cast<ABSU_VehiclePawn>(PlayerController->GetPawn());
        if (Vehicle)
        {
            Vehicle->SetTimer(GameElapsedTime);
        }
	}
}

void ACPP_KY_GS_GamePlay::UpdateGameElapsedTime(int32 GameTime)
{
    GameElapsedTime = GameTime;
    OnRep_GameElapsedTime();
}

void ACPP_KY_GS_GamePlay::MulticastReadyGame_Implementation()
{
    for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
    {
        APlayerController* PlayerController = Iterator->Get();
        if (PlayerController && PlayerController->IsLocalController())
        {
            ABSU_VehiclePawn* Vehicle = Cast<ABSU_VehiclePawn>(PlayerController->GetPawn());
            if (Vehicle)
            {
                Vehicle->ClientReadyGame();
            }
        }
    }
}

void ACPP_KY_GS_GamePlay::MulticastStartGame_Implementation()
{
    // 모든 플레이어 컨트롤러를 가져옴
    for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
    {
        APlayerController* PlayerController = Iterator->Get();
        if (PlayerController && PlayerController->IsLocalController())
        {
            ABSU_VehiclePawn* Vehicle = Cast<ABSU_VehiclePawn>(PlayerController->GetPawn());
            if (Vehicle)
            {
                // 차량을 출발시키는 함수 호출 (예: 가속 시작)
                UE_LOG(LogTemp, Warning, TEXT("Vehicle StartGame"));
                Vehicle->StartGame();
            }
        }
    }
}

void ACPP_KY_GS_GamePlay::MulticastEndGame_Implementation()
{
    for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
    {
        APlayerController* PlayerController = Iterator->Get();
        if (PlayerController && PlayerController->IsLocalController())
        {
            // 여기서 결과 화면 UI를 표시하는 로직을 구현합니다 (예: UMG 위젯 표시)
            // PlayerController->ClientMessage(TEXT("게임이 종료되었습니다! 결과 화면을 표시합니다."));

            ABSU_VehiclePawn* Vehicle = Cast<ABSU_VehiclePawn>(PlayerController->GetPawn());
            if (Vehicle)
            {
                Vehicle->ResultGame(true);
            }
        }
    }
}

void ACPP_KY_GS_GamePlay::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ACPP_KY_GS_GamePlay, GamePlayState);
    DOREPLIFETIME(ACPP_KY_GS_GamePlay, GameElapsedTime);
}

// EReady 3초 후 실행
void ACPP_KY_GS_GamePlay::StartGame()
{
	SetGamePlayState(EGamePlayState::EPlaying);
}
