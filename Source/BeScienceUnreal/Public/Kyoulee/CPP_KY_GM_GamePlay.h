// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_KY_GM_Core.h"
#include "CPP_KY_GM_GamePlay.generated.h"

/**
 * 
 */
UCLASS()
class BESCIENCEUNREAL_API ACPP_KY_GM_GamePlay : public ACPP_KY_GM_Core
{
	GENERATED_BODY()

public:
	// 모든 플레이어를 차량 경주상태로 변경한다.
	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	void TeleportAllPlayersToSpawn();

	FTimerHandle TimerHandle_UpdateGameTime;
	int32 GameTime;
	int32 GameTimeLimit = 5;
	void StartGameTime();

	void EndGame();
	void UpdateGameTime();
};
