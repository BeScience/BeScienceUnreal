// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JsonParseLib.generated.h"

/**
 * 
 */
UCLASS()
class BESCIENCEUNREAL_API UJsonParseLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static bool JsonParse(const FString& json, FString& Name, FString& Message, TArray<uint8>& OutFileData);


	static bool JsonParseMemoAll(const FString& json, TArray<TPair<FString, FVector>>& Memos);

	static FString MakeJson(const TMap<FString, FString> Sources);

	
};
