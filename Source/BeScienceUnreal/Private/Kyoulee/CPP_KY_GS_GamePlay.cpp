// Fill out your copyright notice in the Description page of Project Settings.


#include "Kyoulee/CPP_KY_GS_GamePlay.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/PlayerController.h"
#include "Vehicle/BSU_VehiclePawn.h"
#include "BSU_Mine.h"
#include "Vehicle/BSU_Magnet.h"
#include "EngineUtils.h"
#include <Vehicle/BSU_Star.h>
#include "GameFramework/PlayerState.h"

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
    APlayerState* WinnerPlayerState = GetWinnerPlayerState();

    for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
    {
        APlayerController* PlayerController = Iterator->Get();
        if (PlayerController)
        {
            ABSU_VehiclePawn* Vehicle = Cast<ABSU_VehiclePawn>(PlayerController->GetPawn());
            if (Vehicle)
            {
                APlayerState* state = Vehicle->GetPlayerState();
                if (WinnerPlayerState == state)
                {
                    Vehicle->ResultGame(true);
                }
                else
                {
    				Vehicle->ResultGame(false);
                }
            }
        }
    }

    // ABSU_Mine을 모두 제거
    for (TActorIterator<ABSU_Star> ActorItr(GetWorld()); ActorItr; ++ActorItr)
    {
        ABSU_Star* Mine = *ActorItr;
        Mine->Destroy();
    }

    //// ABSU_Mine을 모두 제거
    //for (TActorIterator<ABSU_Mine> ActorItr(GetWorld()); ActorItr; ++ActorItr)
    //{
    //    ABSU_Mine* Mine = *ActorItr;
    //    Mine->Destroy();
    //}

    // ABSU_Magnet 모두제거
    for (TActorIterator<ABSU_Magnet> ActorItr(GetWorld()); ActorItr; ++ActorItr)
    {
        ABSU_Magnet* Magnet = *ActorItr;
        Magnet->Destroy();
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

APlayerState* ACPP_KY_GS_GamePlay::GetWinnerPlayerState()
{
    APlayerState* WinnerPlayerState = nullptr;
    float HighestScore = -1.0f;

    // 모든 플레이어의 PlayerState를 확인
    for (APlayerState* PlayerState : PlayerArray)
    {
        if (PlayerState && PlayerState->GetScore() > HighestScore)
        {
            // 현재 플레이어의 스코어가 가장 높은 경우 업데이트
            HighestScore = PlayerState->GetScore();
            WinnerPlayerState = PlayerState;
        }
    }

	return WinnerPlayerState;
}
