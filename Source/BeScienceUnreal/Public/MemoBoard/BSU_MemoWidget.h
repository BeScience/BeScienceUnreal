// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BSU_MemoWidget.generated.h"

/**
 * 
 */
UCLASS()
class BESCIENCEUNREAL_API UBSU_MemoWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	// TextBlock bind
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MemoTextBlock;
	void SetMemo(FText text);
};
