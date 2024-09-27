// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HttpFwd.h"
#include "HttpActor.generated.h"


DECLARE_MULTICAST_DELEGATE_TwoParams(FOnResPostTextDelegate, FString, FString);

UCLASS()
class BESCIENCEUNREAL_API AHttpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHttpActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	void ReqPostForm(FString ServerURL, FString form, TArray<uint8>& contents);
	void ReqPostText(FString ServerURL, FString json, TArray<uint8>& contents);
	
	
	void OnResPostText(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	class USoundWaveProcedural* CreateSoundWaveProceduralFromWavData(const TArray<uint8>& RawWavData);

	FOnResPostTextDelegate OnResPostTextDelegate;

		UFUNCTION(BlueprintCallable, Category = "Sound")
	void SendSoundWaveFile(int32 index, FString name, const FString& FilePath);

	int32 IconIndex = 0;

	bool LoadWavFileToByteArray(const FString& FilePath, TArray<uint8>& OutFileData);

	void ReqPostMessage(FString name, FString Message);

	UFUNCTION(BlueprintCallable)
	void DelegateMessage(FString Name, FString Message);

		UPROPERTY(EditDefaultsOnly, Category = "UI")
	TArray<UTexture2D*> Icons;

	
	FString URL = TEXT("http://metaai2.iptime.org:8181/stt-tts-chat");
	//FString URL = TEXT("http://59.13.225.125:8888/stt-tts-chat");
// 	FString URL = TEXT("http://183.109.66.119:8000/stt-tts-chat");
	FString Key = TEXT("/");

	//메시지 
	UPROPERTY()
	class UMessageWidget* MessageWidget;
	
	


};
