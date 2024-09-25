// Fill out your copyright notice in the Description page of Project Settings.


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
		GetWorldTimerManager().SetTimer(GameStartTimer, this, &ACPP_KY_GS_GamePlay::StartGame, 3.0f, false);
	}
	else if (EGamePlayState::EPlaying == GamePlayState)
	{
		// 차량을 출발 시킨다.
        if (HasAuthority())
        {
            // 모든 플레이어 컨트롤러를 가져옴
            for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
            {
                APlayerController* PlayerController = Iterator->Get();
                if (PlayerController && PlayerController->GetPawn())
                {
                    // 플레이어가 포제스한 Pawn이 차량(VehiclePawn)인지 확인
                    ABSU_VehiclePawn* Vehicle = Cast<ABSU_VehiclePawn>(PlayerController->GetPawn());
                    if (Vehicle)
                    {
                        // 차량을 출발시키는 함수 호출 (예: 가속 시작)
                        Vehicle->StartGame();
                    }
                }
            }
        }
		
	}
}

void ACPP_KY_GS_GamePlay::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ACPP_KY_GS_GamePlay, GamePlayState);
}

void ACPP_KY_GS_GamePlay::StartGame()
{
	SetGamePlayState(EGamePlayState::EPlaying);
}
