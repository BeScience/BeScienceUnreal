// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoBoard/BSU_MemoWidget.h"
#include "Components/TextBlock.h"

void UBSU_MemoWidget::SetMemo(FText text)
{
	MemoTextBlock->SetText(text);
}
