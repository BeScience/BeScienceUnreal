// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/QuestWidget.h"
#include "Components/Image.h"

void UQuestWidget::NativeConstruct()
{
	Super::NativeConstruct();

	QuestComplete0->SetVisibility(ESlateVisibility::Hidden);
	QuestComplete1->SetVisibility(ESlateVisibility::Hidden);
	QuestComplete2->SetVisibility(ESlateVisibility::Hidden);
	QuestComplete3->SetVisibility(ESlateVisibility::Hidden);
}

void UQuestWidget::CompleteQuest(int32 QuestIndex)
{
	switch (QuestIndex)
	{
	case 0:
		QuestComplete0->SetVisibility(ESlateVisibility::Visible);
		break;
	case 1:
		QuestComplete1->SetVisibility(ESlateVisibility::Visible);
		break;
	case 2:
		QuestComplete2->SetVisibility(ESlateVisibility::Visible);
		break;
	case 3:
		QuestComplete3->SetVisibility(ESlateVisibility::Visible);
		break;
	}
	if (QuestComplete0->GetVisibility() == ESlateVisibility::Visible &&
		QuestComplete1->GetVisibility() == ESlateVisibility::Visible &&
		QuestComplete2->GetVisibility() == ESlateVisibility::Visible &&
		QuestComplete3->GetVisibility() == ESlateVisibility::Visible)
	{
		this->EndQuest();
	}
}
