// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPP_KY_WG_Login_HUD.generated.h"


/**
 * 
 */
UCLASS()
class BESCIENCEUNREAL_API UCPP_KY_WG_Login_HUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWidgetSwitcher* WS_Login;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UCPP_KY_WG_LoginPage* WBP_LoginPage;

};
