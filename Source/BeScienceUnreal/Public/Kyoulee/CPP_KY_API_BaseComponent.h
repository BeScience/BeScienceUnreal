// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "CPP_KY_API_BaseComponent.generated.h"



USTRUCT ()
struct FJsonPlayerInfo
{
	GENERATED_USTRUCT_BODY ()

	FJsonPlayerInfo () : Id ( 1 ) , Name ( "UnKnown" ) {};

	FJsonPlayerInfo (int32 id, FString name) : Id ( id ) , Name ( name ) { };

	UPROPERTY ()
	int32 Id;

	UPROPERTY ()
	FString Name;

};

USTRUCT ()
struct FJsonPlayerList
{
	GENERATED_USTRUCT_BODY ()

	UPROPERTY ()
	TArray < FJsonPlayerInfo> Players;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BESCIENCEUNREAL_API UCPP_KY_API_BaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCPP_KY_API_BaseComponent();

private:
	FString URLlocal = "http://localhost:3000/api";

	FString URLConfig ();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool UseGlobal = true;

	UPROPERTY ( EditDefaultsOnly , BlueprintReadWrite )
	FString URLGlobal = "https://unreal-next-api.vercel.app/api";

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void HttpGetCall ();

	virtual void OnResHttpGetCallBack ( FHttpRequestPtr req , FHttpResponsePtr res , bool bConnectedSuccessfully );

	virtual void HttpPostCall ();

	virtual void OnResHttpPostCallBack ( FHttpRequestPtr req , FHttpResponsePtr res , bool bConnectedSuccessfully );


	FJsonPlayerList JsonPersePlayerList (FString something, ...);

	FString JsonStringfyPlayerList ( FJsonPlayerList playerList );


	//UPROPERTY ( EditDefaultsOnly , BlueprintReadWrite )
	//class UInputAction* IA_API;
	
	void AddPlayerInputComponent ( UInputComponent* PlayerInputComponent );

	
};
