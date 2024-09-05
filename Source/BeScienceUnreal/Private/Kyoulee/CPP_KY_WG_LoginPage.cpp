// Fill out your copyright notice in the Description page of Project Settings.


#include "Kyoulee/CPP_KY_WG_LoginPage.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Interfaces/IHttpBase.h"
#include "Json.h"
#include "JsonObjectConverter.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"

void UCPP_KY_WG_LoginPage::NativeConstruct()
{
	if (BT_Ok)
	{
		BT_Ok->OnClicked.AddDynamic(this, &UCPP_KY_WG_LoginPage::LoginButtonOnClick);
	}
}

void UCPP_KY_WG_LoginPage::LoginButtonOnClick()
{
	if (bHttpWaitresponse)
		return;
	bHttpWaitresponse = true;
	HttpPostLoginCall(this->ET_Name->GetText().ToString(), this->ET_PassWord->GetText().ToString());
}


void UCPP_KY_WG_LoginPage::HttpPostLoginCall(FString username, FString password)
{
	UE_LOG(LogTemp, Display, TEXT("HttpPostLoginCall"));
	FHttpModule& httpModule = FHttpModule::Get();

	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();

	FJsonPlayer player(username, password);
	FString json = UIJsonStringfyPlayer(player);

	req->SetURL(this->URLLogin);
	req->SetVerb("POST");
	req->SetHeader("content-type", "application/json");
	req->SetContentAsString(json);

	req->OnProcessRequestComplete().BindUObject(this, &UCPP_KY_WG_LoginPage::OnResHttpPostLoginCallBack);

	req->ProcessRequest();
}

void UCPP_KY_WG_LoginPage::OnResHttpPostLoginCallBack(FHttpRequestPtr req, FHttpResponsePtr res, bool bConnectedSuccessfully)
{
	UE_LOG(LogTemp, Warning, TEXT("OnResHttpPostLoginCallBack"));
	if (bConnectedSuccessfully)
	{
		FString result = res->GetContentAsString();
		//	FJsonPlayer playerlist = UIJsonPersePlayer(result);
		UE_LOG(LogTemp, Warning, TEXT("[POST] player id %s  ??  %d"), *result, res->GetResponseCode());
		if (res->GetStatus() == 200)
		{
			//성공 했을때 동작 추가
			MyNativeLoginEvent();
		}
	}
	bHttpWaitresponse = false;
}


FString UCPP_KY_WG_LoginPage::UIJsonStringfyPlayer(FJsonPlayer player)
{
	TSharedPtr<FJsonObject> JsonObject = FJsonObjectConverter::UStructToJsonObject<FJsonPlayer>(player);;
	FString jsonStr = "";
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&jsonStr);

	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

	return jsonStr;
}

FJsonPlayer UCPP_KY_WG_LoginPage::UIJsonPersePlayer(FString something)
{
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(something);

	FJsonPlayer Player;
	TSharedPtr<FJsonObject> JsonObject;

	FJsonSerializer::Deserialize(JsonReader, JsonObject);

	FJsonObjectConverter::JsonObjectToUStruct<FJsonPlayer>(JsonObject.ToSharedRef(), &Player);

	return Player;
}
