// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_KY_WG_LoginJoinPage.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Interfaces/IHttpBase.h"
#include "Json.h"
#include "JsonObjectConverter.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "CPP_KY_WG_Login_HUD.h"

void UCPP_KY_WG_LoginJoinPage::NativeConstruct()
{
	this->BT_Ok->OnClicked.AddDynamic(this, &UCPP_KY_WG_LoginJoinPage::JoinButtonOnClick);
}

void UCPP_KY_WG_LoginJoinPage::JoinButtonOnClick()
{
	if (ET_Password->GetText().ToString() != ET_PasswordCheck->GetText().ToString())
		return;
	if (bHttpWaitresponse)
		return;
	UE_LOG(LogTemp, Display, TEXT("JoinButtonOnClick"));
	bHttpWaitresponse = true;
	HttpPostJoinCall(ET_Name->GetText().ToString(), ET_Password->GetText().ToString());
}

void UCPP_KY_WG_LoginJoinPage::HttpPostJoinCall(FString username, FString password)
{
	UE_LOG(LogTemp, Display, TEXT("HttpPostJoinCall"));
	FHttpModule& httpModule = FHttpModule::Get();

	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();

	FJsonPlayer player(username, password);
	FString json = JsonStringfyJoinPlayer(player);

	req->SetURL(this->URLLogin);
	req->SetVerb("POST");
	req->SetHeader("content-type", "application/json");
	req->SetContentAsString(json);

	req->OnProcessRequestComplete().BindUObject(this, &UCPP_KY_WG_LoginJoinPage::OnResHttpPostJoinCallBack);

	req->ProcessRequest();
}

void UCPP_KY_WG_LoginJoinPage::OnResHttpPostJoinCallBack(FHttpRequestPtr req, FHttpResponsePtr res, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		FString result = res->GetContentAsString();
		//	FJsonPlayer playerlist = UIJsonPersePlayer(result);
		UE_LOG(LogTemp, Warning, TEXT("[POST] player id %s  ??  %d"), *result, res->GetResponseCode());
		if (res->GetResponseCode() == 200)
		{
			//성공 했을때 동작 추가
			MyNativeEvent();
		}
	}
	bHttpWaitresponse = false;
}

FString UCPP_KY_WG_LoginJoinPage::JsonStringfyJoinPlayer(FJsonPlayer player)
{
	TSharedPtr<FJsonObject> JsonObject = FJsonObjectConverter::UStructToJsonObject<FJsonPlayer>(player);;
	FString jsonStr = "";
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&jsonStr);

	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

	return jsonStr;
}