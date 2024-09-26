// Fill out your copyright notice in the Description page of Project Settings.


#include "Kyoulee/CPP_KY_GM_GamePlay.h"
#include "Vehicle/BSU_VehiclePawn.h"
#include "Kismet/GameplayStatics.h"
#include "Vehicle/BSU_StartLocation.h"
#include "BaseCharacter.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PawnMovementComponent.h"
#include "EngineUtils.h"
#include "Kyoulee/CPP_KY_GS_GamePlay.h"

void ACPP_KY_GM_GamePlay::TeleportAllPlayersToSpawn()
{
    // TeleportAllPlayersToSpawn로그
    UE_LOG(LogTemp, Warning, TEXT("TeleportAllPlayersToSpawn"));

    // 모든 차량을 가져온다.
    TArray<AActor*> FoundKarts;
    for (TActorIterator<ABSU_VehiclePawn> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		FoundKarts.Add(*ActorItr);
	}

    // 모든 차량 위치를 가져온다.
    TArray<AActor*> FoundLocKarts;
    for (TActorIterator<ABSU_StartLocation> ActorItr(GetWorld()); ActorItr; ++ActorItr)
    {
        FoundLocKarts.Add(*ActorItr);
    }
    
    int i = 0;
    // 월드에서 모든 플레이어 컨트롤러를 가져옴
    for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
    {
        APlayerController* PlayerController = Iterator->Get();
        ABaseCharacter* Player = Cast<ABaseCharacter>(PlayerController->GetPawn());
        if (Player)
        {
            //플레이어를 차량에 포제스한다.
        }

        if (PlayerController && PlayerController->GetPawn())
        {
            APawn* pawn = PlayerController->GetPawn();
            // FoundLocKarts[i]; 위치로 이동시킨다.
            // pawn의 각속도와 속도를 0으로 만듬.
            pawn->GetMovementComponent()->Velocity = FVector::ZeroVector;

            if (i < FoundLocKarts.Num())
            {
                pawn->SetActorLocation(FoundLocKarts[i]->GetActorLocation(), false, NULL, ETeleportType::TeleportPhysics);
                pawn->SetActorRotation(FoundLocKarts[i]->GetActorRotation(), ETeleportType::TeleportPhysics);
                i++;
            }
        }
    }
}

void ACPP_KY_GM_GamePlay::StartGameTime()
{
    GetWorld()->GetTimerManager().SetTimer(TimerHandle_UpdateGameTime, this, &ACPP_KY_GM_GamePlay::UpdateGameTime, 1.0f, true);

    GameTime = GameTimeLimit;
}

void ACPP_KY_GM_GamePlay::EndGame()
{
    // 타이머 지우기
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_UpdateGameTime);

    // 모든 플레이어에게 결과창을 띄운다.

    ACPP_KY_GS_GamePlay* GamePlayState = GetGameState<ACPP_KY_GS_GamePlay>();
    if (GamePlayState)
    {
        GamePlayState->SetGamePlayState(EGamePlayState::EGameOver);
    }
}

void ACPP_KY_GM_GamePlay::UpdateGameTime()
{
	GameTime--;
	if (GameTime <= 0)
	{
		EndGame();
	}

	ACPP_KY_GS_GamePlay* GamePlayState = GetGameState<ACPP_KY_GS_GamePlay>();
	if (GamePlayState)
	{
		GamePlayState->UpdateGameElapsedTime(GameTime);
	}
}
