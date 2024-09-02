// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_KY_PC_Core.h"
#include "CPP_KY_WG_Gameplay_HUD.h"
#include "CPP_KY_PC_GamePlay.generated.h"

/**
 * 
 */
UCLASS()
class BESCIENCEUNREAL_API ACPP_KY_PC_GamePlay : public ACPP_KY_PC_Core
{
	GENERATED_BODY()

private:
	UCPP_KY_WG_Gameplay_HUD* WBP_Gameplay_HUD;

public:
	virtual void BeginPlay () override;

	UPROPERTY ( EditDefaultsOnly , BlueprintReadWrite , Category = "WidgetView" )
	TSubclassOf<UCPP_KY_WG_Gameplay_HUD> WBP_Gameplay_HUD_Class;

};
