// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoBoard/BSU_MemoEditWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"

void UBSU_MemoEditWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AttachButton->OnClicked.AddDynamic(this, &UBSU_MemoEditWidget::OnAttachMemo);
	CancelButton->OnClicked.AddDynamic(this, &UBSU_MemoEditWidget::OnCancelMemo);
}

void UBSU_MemoEditWidget::OnAttachMemo()
{
	// 사운드 재생
	
	UGameplayStatics::PlaySound2D(GetWorld(), sound);

	FString memo = MemoEditTextBox->GetText().ToString();
	// 위젯 숨김
	RemoveFromParent();
	if (OnAttachMemoDelegate.IsBound())
		OnAttachMemoDelegate.Execute(memo);
}

void UBSU_MemoEditWidget::OnCancelMemo()
{
	UGameplayStatics::PlaySound2D(GetWorld(), sound);
	// 위젯을 숨김
	RemoveFromParent();
}
