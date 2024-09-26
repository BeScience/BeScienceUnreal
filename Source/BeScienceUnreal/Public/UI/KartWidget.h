// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KartWidget.generated.h"

/**
 * 
 */
UCLASS()
class BESCIENCEUNREAL_API UKartWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	// 상대방 플레이어들의 이름을 우측에 나열하고 싶다.
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* txt_users;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* StartText;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* GameTimeText;

	// UI 애니메이션
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* StartRacing;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Lose;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Win;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USoundBase* StartSound;

public:
	void SetGameTime(int32 Time);
	void ShowStartText(bool value);
	void ShowPlayGame();
	void ShowWin();
	void ShowLose();
};
