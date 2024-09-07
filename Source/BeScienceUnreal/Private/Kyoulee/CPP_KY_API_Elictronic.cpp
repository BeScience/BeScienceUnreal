// Fill out your copyright notice in the Description page of Project Settings.


#include "Kyoulee/CPP_KY_API_Elictronic.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Interfaces/IHttpBase.h"
#include "Json.h"
#include "JsonObjectConverter.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"

// Sets default values
ACPP_KY_API_Elictronic::ACPP_KY_API_Elictronic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_KY_API_Elictronic::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_KY_API_Elictronic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void ACPP_KY_API_Elictronic::HttpGetElictronicCall()
{
	if (!this->HttpCallEnd) {
		return;
	}
	this->HttpCallEnd = false;
	FHttpModule& httpModule = FHttpModule::Get();

	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();

	req->SetURL(URLElictronic);
	req->SetVerb("POST");
	req->SetHeader("content-type", "application/json");

	req->OnProcessRequestComplete().BindUObject(this, &ACPP_KY_API_Elictronic::OnResHttpPostElictronicCallBack);

	req->ProcessRequest();
}

void ACPP_KY_API_Elictronic::OnResHttpPostElictronicCallBack(FHttpRequestPtr req, FHttpResponsePtr res, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		FString result = res->GetContentAsString();
		//	FJsonPlayer playerlist = UIJsonPersePlayer(result);
		UE_LOG(LogTemp, Warning, TEXT("[Get] OnResHttpGetElictornicCallBack id %s  ??  %d"), *result, res->GetResponseCode());
		if (res->GetResponseCode() == 200)
		{
			//성공 했을때 동작 추가
			HttpCallBack(FVector(1));
		}
	}
	this->HttpCallEnd = true;

}

FJsonElictronic ACPP_KY_API_Elictronic::UIJsonPerseElictronic(FString something)
{
	return FJsonElictronic();
}

