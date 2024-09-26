// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BSU_MemoEditWidget.generated.h"

// 델리게이트 선언
DECLARE_DELEGATE_OneParam(FMyMemoDelegate, const FString&);

/**
 * 
 */
UCLASS()
class BESCIENCEUNREAL_API UBSU_MemoEditWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	// 에디트 텍스트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UEditableTextBox* MemoEditTextBox;

	UFUNCTION(BlueprintImplementableEvent)
	void ShowMemoEditWidget();

	UFUNCTION(BlueprintImplementableEvent)
	void ShowAttachMemo();

	UFUNCTION()
	void OnAttachMemo();
	UFUNCTION()
	void OnCancelMemo();

	FMyMemoDelegate OnAttachMemoDelegate;

	//바인드
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* AttachButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* CancelButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* sound;
};
