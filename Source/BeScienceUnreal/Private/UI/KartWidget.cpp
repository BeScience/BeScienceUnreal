// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/KartWidget.h"
#include "Components/TextBlock.h"
#include "Animation/WidgetAnimation.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/GameStateBase.h"

void UKartWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	// 1. 다른 플레이어들의 정보를 알고싶다.
	TArray<TObjectPtr<APlayerState>> users = GetWorld()->GetGameState()->PlayerArray;

	// 2. 플레이어들의 이름을 다 모아서 
	FString names;
	for (APlayerState* user : users)
	{
		names.Append(FString::Printf(TEXT("%s : %d\n"), *user->GetPlayerName(), (int32)user->GetScore()));
	}

	// 3. 출력하고 싶다.
	txt_users->SetText(FText::FromString(names));
}

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
