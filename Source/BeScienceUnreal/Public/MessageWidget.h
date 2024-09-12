// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MessageWidget.generated.h"

/**
 * 
 */
UCLASS()
class BESCIENCEUNREAL_API UMessageWidget : public UUserWidget
{
	GENERATED_BODY()

public: 
	void ShowDialogForDuration(UTexture2D* Icon, FString Name, FString Description);

	
};
