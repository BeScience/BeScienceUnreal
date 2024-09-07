// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "CPP_KY_API_Elictronic.generated.h"

USTRUCT(BlueprintType)
struct FJsonElictronicHandPoint
{
	GENERATED_USTRUCT_BODY()

		FJsonElictronicHandPoint() : index(0), x(0), y(0), z(0){};

	UPROPERTY()
	int32 index;
	UPROPERTY()
	float x;
	UPROPERTY()
	float y;
	UPROPERTY()
	float z;
};

USTRUCT(BlueprintType)
struct FJsonElictronic
{
	GENERATED_USTRUCT_BODY()

	FJsonElictronic() : gesture("0"), landmarks(){};

	UPROPERTY()
	FString gesture;

	UPROPERTY()
	TArray<FJsonElictronicHandPoint> landmarks;
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
	
	UPROPERTY(BlueprintReadWrite)
	bool HttpCallEnd = true;

	UFUNCTION(BlueprintImplementableEvent)
	void HttpCallBack(FVector HandPosition);

	void OnResHttpPostElictronicCallBack(FHttpRequestPtr req, FHttpResponsePtr res, bool bConnectedSuccessfully);

	UFUNCTION(BlueprintCallable)
	FJsonElictronic UIJsonPerseElictronic(FString something);


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString URLElictronic = "59.13.225.125:8888/mediapipe";
};
