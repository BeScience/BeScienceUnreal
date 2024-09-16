// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoBoard/BSU_MemoHttpComponent.h"
#include "HttpModule.h"
#include "JsonParseLib.h"
#include "Http.h"
#include "MemoBoard/BSU_MemoBoard.h"

// Sets default values for this component's properties
UBSU_MemoHttpComponent::UBSU_MemoHttpComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBSU_MemoHttpComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Me = Cast<ABSU_MemoBoard>(GetOwner());
}

void UBSU_MemoHttpComponent::AttachMemo(FString memo, FVector3d pos)
{
	TMap <FString, FString> studentData;
	studentData.Add("text", memo);
	// json to byte
	float x = pos.X;
	float y = pos.Y;
	float z = pos.Z;
	// studentData.Add("x", x.ToString());
	studentData.Add("x", FString::SanitizeFloat(x));
	studentData.Add("y", FString::SanitizeFloat(y));
	studentData.Add("z", FString::SanitizeFloat(z));

	FString json = UJsonParseLib::MakeJson(studentData);

	ReqPostAttachMemo(json);
}

void UBSU_MemoHttpComponent::ReqPostAttachMemo(FString json)
{
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();
	req->SetURL(URL);
	req->SetVerb(TEXT("POST"));

	req->SetHeader(TEXT("content-type"), TEXT("application/json"));
	req->SetContentAsString(json);

	UE_LOG(LogTemp, Warning, TEXT("ReqPostText... %d"), json.Len());
	req->OnProcessRequestComplete().BindUObject(this, &UBSU_MemoHttpComponent::OnResPostAttachMemo);

	req->ProcessRequest();
}

void UBSU_MemoHttpComponent::OnResPostAttachMemo(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnResPostAttachMemo... "));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OnResPostAttachMemo... failed"));
	}
}

void UBSU_MemoHttpComponent::ReqPostGetAllMemo()
{
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();
	req->SetURL(URL);
	req->SetVerb(TEXT("Get"));

	req->SetHeader(TEXT("content-type"), TEXT("application/json"));

	req->OnProcessRequestComplete().BindUObject(this, &UBSU_MemoHttpComponent::OnResPostGetAllMemo);

	req->ProcessRequest();
}

void UBSU_MemoHttpComponent::OnResPostGetAllMemo(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	FString ret = Response->GetContentAsString();

	// json 파싱

	TArray<TPair<FString, FVector>> Memos;

	if (UJsonParseLib::JsonParseMemoAll(ret, Memos))
	{
		for (TPair<FString, FVector> Memo : Memos)
		{
			Me->AddMemo(Memo.Value, Memo.Key);
		}
	}
}

void UBSU_MemoHttpComponent::ReqPostRemoveAllMemo()
{
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();
	req->SetURL(URL);
	req->SetVerb(TEXT("POST"));

	req->SetHeader(TEXT("content-type"), TEXT("application/json"));

	req->OnProcessRequestComplete().BindUObject(this, &UBSU_MemoHttpComponent::OnResPostRemoveAllMemo);

	req->ProcessRequest();
}

void UBSU_MemoHttpComponent::OnResPostRemoveAllMemo(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{

}
