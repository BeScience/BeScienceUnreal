// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "CPP_KY_WG_LoginPage.generated.h"

USTRUCT(BlueprintType)
struct FJsonPlayer
{
	GENERATED_USTRUCT_BODY()

		FJsonPlayer() : username("name"), password("UnKnown"){};

	FJsonPlayer(FString name, FString password) : username(name), password(password){ };

	UPROPERTY()
		FString username;

	UPROPERTY()
		FString password;
};

/**
 * 
 */
UCLASS()
class BESCIENCEUNREAL_API UCPP_KY_WG_LoginPage : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* ET_Name;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* ET_PassWord;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* BT_Ok;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* BT_Cancel;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void LoginButtonOnClick();

	bool bHttpWaitresponse = false;

	UFUNCTION(BlueprintImplementableEvent)
	void MyNativeLoginEvent();
public:

	UFUNCTION(BlueprintCallable)
	void HttpPostLoginCall(FString username, FString password);

	void OnResHttpPostLoginCallBack(FHttpRequestPtr req, FHttpResponsePtr res, bool bConnectedSuccessfully);

	UFUNCTION(BlueprintCallable)
		FString UIJsonStringfyPlayer(FJsonPlayer player);

	UFUNCTION(BlueprintCallable)
		FJsonPlayer UIJsonPersePlayer(FString something);


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FString URLLogin = "http://mtvs-museum.duckdns.org:8080/v1/auth/login";

};
