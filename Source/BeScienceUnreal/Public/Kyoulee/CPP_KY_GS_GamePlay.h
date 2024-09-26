// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_KY_GS_Core.h"
#include "CPP_KY_GS_GamePlay.generated.h"

UENUM(BlueprintType)
enum class EGamePlayState : uint8
{
	EWaiting UMETA(DisplayName = "Waiting"),
	EReady UMETA(DisplayName = "Ready"),
	EPlaying UMETA(DisplayName = "Playing"),
	EGameOver UMETA(DisplayName = "GameOver"),
};

/**
 * 
 */
UCLASS()
class BESCIENCEUNREAL_API ACPP_KY_GS_GamePlay : public ACPP_KY_GS_Core
{
	GENERATED_BODY()
	
public:

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "GameState")
	EGamePlayState GamePlayState;

	UFUNCTION(BlueprintCallable, Category = "GameState")
	void SetGamePlayState(EGamePlayState NewGamePlayState);

	
    UPROPERTY(ReplicatedUsing = OnRep_GameElapsedTime, BlueprintReadOnly, Category = "Game Time")
    int32 GameElapsedTime;
	
    UFUNCTION()
    void OnRep_GameElapsedTime();

	void UpdateGameElapsedTime(int32 GameTime);

	UFUNCTION(NetMulticast, Reliable)
    void MulticastReadyGame();
	UFUNCTION(NetMulticast, Reliable)
    void MulticastStartGame();
	UFUNCTION(NetMulticast, Reliable)
    void MulticastEndGame();

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	FTimerHandle GameStartTimer;

	UFUNCTION()
	void StartGame();

	APlayerState* GetWinnerPlayerState();


};
