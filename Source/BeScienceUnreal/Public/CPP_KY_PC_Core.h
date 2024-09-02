// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPP_KY_PC_Core.generated.h"

/**
 * 
 */
UCLASS()
class BESCIENCEUNREAL_API ACPP_KY_PC_Core : public APlayerController
{
	GENERATED_BODY()

private:
	class UCPP_KY_WG_GameMenu* WBP_GameMenu;

	/**
	* @memo 함수명을 바꾸는게 좋을거 같음 메모
	*/
	void FucusWidget ( APlayerController* PlayerController , UUserWidget* TargetWidget );

public:
	virtual void BeginPlay () override;

	UPROPERTY (EditDefaultsOnly, BlueprintReadWrite, Category = "WidgetView" )
	TSubclassOf<class UCPP_KY_WG_GameMenu> WBP_GameMenu_Class;

	UFUNCTION ( BlueprintCallable , Category = "WidgetView" )
	void ToggleGameMenu ();

};
