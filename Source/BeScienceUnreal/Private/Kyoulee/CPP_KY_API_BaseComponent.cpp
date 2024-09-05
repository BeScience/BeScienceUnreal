// Fill out your copyright notice in the Description page of Project Settings.


#include "Kyoulee/CPP_KY_API_BaseComponent.h"
#include "InputAction.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Interfaces/IHttpBase.h"
#include "Json.h"
#include "JsonObjectConverter.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"

// Sets default values for this component's properties
UCPP_KY_API_BaseComponent::UCPP_KY_API_BaseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	//ConstructorHelpers::FObjectFinder<UInputAction> tempInput ( TEXT ( "/Script/EnhancedInput.InputAction'/Game/Kyoulee/Inputs/Actions/IA_API.IA_API'" ) );
	//if (tempInput.Succeeded ())
	//{
	//	this->IA_API = tempInput.Object;
	//}
}


FString UCPP_KY_API_BaseComponent::URLConfig ()
{

	return  UseGlobal ? this->URLGlobal : this->URLlocal;
}

// Called when the game starts
void UCPP_KY_API_BaseComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	HttpGetCall ();
	HttpPostCall ();
}


// Called every frame
void UCPP_KY_API_BaseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCPP_KY_API_BaseComponent::HttpGetCall ()
{
	FHttpModule& httpModule = FHttpModule::Get ();

	TSharedRef<IHttpRequest> req = httpModule.CreateRequest ();

	req->SetURL ( URLConfig ());
	req->SetVerb ( "GET" );
	req->SetHeader ( "content-type" , "application/json" );
	req->SetHeader ( "Access-Control-Allow-Origin" , "*" );

	req->OnProcessRequestComplete ().BindUObject (this, &UCPP_KY_API_BaseComponent::OnResHttpGetCallBack);

	req->ProcessRequest ();
}

void UCPP_KY_API_BaseComponent::OnResHttpGetCallBack ( FHttpRequestPtr req , FHttpResponsePtr res , bool bConnectedSuccessfully )
{
	UE_LOG ( LogTemp , Warning , TEXT ( "[GET] call back  %d" ), req.Get()->GetContentLength() );
	
}

void UCPP_KY_API_BaseComponent::HttpPostCall ()
{
	FHttpModule& httpModule = FHttpModule::Get ();

	TSharedRef<IHttpRequest> req = httpModule.CreateRequest ();

	FJsonPlayerList playerlist;
	playerlist.Players.Add ( FJsonPlayerInfo ( 0 , "Test" ) );
	FString json = JsonStringfyPlayerList ( playerlist );

	req->SetURL ( URLConfig () );
	req->SetVerb ( "POST" );
	req->SetHeader ( "content-type" , "application/json" );
	req->SetContentAsString ( json );
	
	req->OnProcessRequestComplete ().BindUObject ( this , &UCPP_KY_API_BaseComponent::OnResHttpPostCallBack );

	req->ProcessRequest ();

}

void UCPP_KY_API_BaseComponent::OnResHttpPostCallBack ( FHttpRequestPtr req , FHttpResponsePtr res , bool bConnectedSuccessfully )
{
	if (bConnectedSuccessfully)
	{
		FString result = res->GetContentAsString ();
		FJsonPlayerList playerlist = JsonPersePlayerList ( result );
		for (FJsonPlayerInfo player : playerlist.Players)
		{
			UE_LOG ( LogTemp , Display , TEXT ( "[POST] player id %d  name : %s" ) , player.Id, *player.Name );
		}
	}
}




FJsonPlayerList UCPP_KY_API_BaseComponent::JsonPersePlayerList ( FString something , ...)
{
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create ( something );

	FJsonPlayerList PlayerList;
	TSharedPtr<FJsonObject> JsonObject;

	FJsonSerializer::Deserialize ( JsonReader , JsonObject );

	FJsonObjectConverter::JsonObjectToUStruct<FJsonPlayerList> ( JsonObject.ToSharedRef () , &PlayerList );

	return PlayerList;

}

FString UCPP_KY_API_BaseComponent::JsonStringfyPlayerList ( FJsonPlayerList playerList )
{
	FJsonPlayerInfo t = FJsonPlayerInfo ( 1 , "MyNameTest" );
	playerList.Players.Add ( t );

	TSharedPtr<FJsonObject> JsonObject = FJsonObjectConverter::UStructToJsonObject<FJsonPlayerList> ( playerList );;
	FString jsonStr = "";
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create ( &jsonStr );

	FJsonSerializer::Serialize ( JsonObject.ToSharedRef () , JsonWriter );

	return jsonStr;
}

void UCPP_KY_API_BaseComponent::AddPlayerInputComponent ( UInputComponent* PlayerInputComponent )
{

}

