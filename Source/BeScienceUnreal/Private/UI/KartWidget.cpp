// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/KartWidget.h"
#include "Components/TextBlock.h"
#include "Animation/WidgetAnimation.h"

void UKartWidget::SetGameTime(int32 Time)
{
	if (GameTimeText)
	{
		// 00:00 형식으로 시간을 표시한다.
		int32 Min = Time / 60;
		int32 Sec = Time % 60;
		FString TimeString = FString::Printf(TEXT("%02d:%02d"), Min, Sec);
		GameTimeText->SetText(FText::FromString(TimeString));
	}
}

void UKartWidget::ShowStartText(bool value)
{
	if (StartText)
	{
		StartText->SetVisibility(value ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}

void UKartWidget::ShowPlayGame()
{
	PlayAnimation(StartRacing);
}

void UKartWidget::ShowWin()
{
	PlayAnimation(Win);
}

void UKartWidget::ShowLose()
{
	PlayAnimation(Lose);
}
