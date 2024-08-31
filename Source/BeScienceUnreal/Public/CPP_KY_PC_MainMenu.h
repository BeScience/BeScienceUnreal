// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPP_KY_PC_MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class BESCIENCEUNREAL_API ACPP_KY_PC_MainMenu : public APlayerController
{
	GENERATED_BODY()

private:
	class UCPP_KY_WG_MainMenu* WBP_MainMenu;

public:
	virtual void BeginPlay () override;

	UPROPERTY ( EditDefaultsOnly , BlueprintReadWrite , Category = "WidgetView" )
	TSubclassOf<class UCPP_KY_WG_MainMenu> WBP_MainMenu_Class;



};
