// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "CPP_KY_API_Elictronic.generated.h"

USTRUCT(BlueprintType)
struct FJsonElictronic
{
	GENERATED_USTRUCT_BODY()

	FJsonElictronic() : gesture("name"){};

	FJsonElictronic(FString name, FString password) : gesture(name){ };

	UPROPERTY()
		FString gesture;

};


UCLASS()
class BESCIENCEUNREAL_API ACPP_KY_API_Elictronic : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_KY_API_Elictronic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable)
	void HttpGetElictronicCall();

	void OnResHttpPostElictronicCallBack(FHttpRequestPtr req, FHttpResponsePtr res, bool bConnectedSuccessfully);

	UFUNCTION(BlueprintCallable)
	FJsonElictronic UIJsonPerseElictronic(FString something);


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString URLElictronic = "59.13.225.125:8888/mediapipe";
};
