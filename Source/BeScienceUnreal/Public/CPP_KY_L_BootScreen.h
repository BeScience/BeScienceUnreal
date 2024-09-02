// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_KY_WG_BootScreen.h"
#include "Engine/LevelScriptActor.h"
#include "CPP_KY_L_BootScreen.generated.h"

/**
 * 
 */
UCLASS()
class BESCIENCEUNREAL_API ACPP_KY_L_BootScreen : public ALevelScriptActor
{
	GENERATED_BODY()

private:
	UCPP_KY_WG_BootScreen* WBP_BootScreen;

public:
	virtual void BeginPlay () override;

	UPROPERTY ( EditDefaultsOnly , BlueprintReadWrite , Category = "WidgetView" )
	TSubclassOf<UCPP_KY_WG_BootScreen> WBP_BootScreen_Class;
};
