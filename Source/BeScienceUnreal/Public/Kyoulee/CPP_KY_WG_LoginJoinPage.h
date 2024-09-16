// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPP_KY_WG_LoginPage.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "CPP_KY_WG_LoginJoinPage.generated.h"

/*
 *
 */
UCLASS()
class BESCIENCEUNREAL_API UCPP_KY_WG_LoginJoinPage : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UEditableTextBox* ET_Name;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UEditableTextBox* ET_Password;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UEditableTextBox* ET_PasswordCheck;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* BT_Ok;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* BT_Cancel;

	/*UFUNCTION(BlueprintImplementableEvent)
	void MyNativeEvent();*/
	UFUNCTION(BlueprintImplementableEvent)
	void MyNativeEvent();

	UPROPERTY(BlueprintReadOnly)
	int32 HttpStatus;
	
	UPROPERTY(BlueprintReadOnly)
	FString HttpResult;

	UFUNCTION(BlueprintCallable)
	int32 HttpStatusValue();

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
		void JoinButtonOnClick();

	bool bHttpWaitresponse = false;

	UFUNCTION()
	void HttpPostJoinCall(FString username, FString password);

	void OnResHttpPostJoinCallBack(FHttpRequestPtr req, FHttpResponsePtr res, bool bConnectedSuccessfully);

	FString JsonStringfyJoinPlayer(FJsonPlayer player);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FString URLLogin = "http://mtvs-museum.duckdns.org:8080/v1/auth/join";
};
