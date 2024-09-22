// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TranscriptWidget.generated.h"

/**
 * 
 */
UCLASS()
class BESCIENCEUNREAL_API UTranscriptWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void AnimNextWidget();

	UFUNCTION(BlueprintImplementableEvent)
	void AnimStartWidget();
	

		UFUNCTION(BlueprintImplementableEvent)
	void AnimHideWidget();


	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TranscriptText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class URichTextBlock* MessageText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString MessageStr;

	float yPos = 0.0f;

	
};
