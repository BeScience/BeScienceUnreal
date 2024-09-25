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
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* StartText;

	// UI 애니메이션
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* StartRacing;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Lose;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Win;

public:

	void ShowStartText(bool value);
	void ShowPlayGame();
	void ShowWin();
	void ShowLose();
};
