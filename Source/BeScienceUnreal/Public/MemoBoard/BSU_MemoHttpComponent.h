// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HttpFwd.h"
#include "BSU_MemoHttpComponent.generated.h"

// 델리게이트 선언

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BESCIENCEUNREAL_API UBSU_MemoHttpComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBSU_MemoHttpComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	void AttachMemo(FString memo, FVector3d pos);

	void ReqPostAttachMemo(FString json);
	void OnResPostAttachMemo(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void ReqPostGetAllMemo();
	void OnResPostGetAllMemo(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void ReqPostRemoveAllMemo();
	void OnResPostRemoveAllMemo(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	FString URL = TEXT("http://mtvs-museum.duckdns.org:8080/postit");

	class ABSU_MemoBoard* Me;
};
