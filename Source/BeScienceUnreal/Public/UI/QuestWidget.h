// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestWidget.generated.h"

/**
 * 
 */
UCLASS()
class BESCIENCEUNREAL_API UQuestWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	// 생성자
	virtual void NativeConstruct() override;

	// 바인드
	UPROPERTY(meta = (BindWidget))
	class UImage* QuestComplete0;

	UPROPERTY(meta = (BindWidget))
	class UImage* QuestComplete1;

	UPROPERTY(meta = (BindWidget))
	class UImage* QuestComplete2;

	UPROPERTY(meta = (BindWidget))
	class UImage* QuestComplete3;

	void CompleteQuest(int32 QuestIndex);
};
