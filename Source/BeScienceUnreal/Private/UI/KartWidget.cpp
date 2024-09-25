// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/KartWidget.h"
#include "Components/TextBlock.h"
#include "Animation/WidgetAnimation.h"

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
