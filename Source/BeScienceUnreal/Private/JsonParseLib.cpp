// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonParseLib.h"
#include "CoreMinimal.h"

bool UJsonParseLib::JsonParse(const FString& json, FString& Name, FString& Message, TArray<uint8>& OutFileData)
{
	FString resultValue;

	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(json);
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject);
	if (FJsonSerializer::Deserialize(reader, result))
	{
		Name = result->GetStringField(TEXT("docent"));
		FString VoiceData = result->GetStringField(TEXT("resultwav"));
		Message = result->GetStringField(TEXT("msg"));

		FBase64::Decode(VoiceData, OutFileData);
	}

	return true;
}

bool UJsonParseLib::JsonParseMemoAll(const FString& json, TArray<TPair<FString, FVector>>& Memos)
{
	/**
	 * 
	 [
		{"text":"string","x":"string","y":"string","z":"string"},
		{"text":null,"x":"-208.791321","y":"0.000003","z":"457.506073"},
		{"text":"과학","x":"-84.932098","y":"0.000001","z":"567.2099"},
		{"text":"과학2","x":"235.332382","y":"-0.000003","z":"448.658997"},
		{"text":"과학2","x":"235.332382","y":"-0.000003","z":"448.658997"}
	]
	 */

	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(json);
	TArray<TSharedPtr<FJsonValue>> result;

	if (!FJsonSerializer::Deserialize(reader, result))
	{
		return false;
	}

	for (TSharedPtr<FJsonValue> Value : result)
	{
		TSharedPtr<FJsonObject> Object = Value->AsObject();
		FString text = Object->GetStringField(TEXT("text"));
		FString x = Object->GetStringField(TEXT("x"));
		FString y = Object->GetStringField(TEXT("y"));
		FString z = Object->GetStringField(TEXT("z"));

		FVector pos(FCString::Atof(*x), FCString::Atof(*y), FCString::Atof(*z));
		Memos.Add(TPair<FString, FVector>(text, pos));
	}

	return true;
}

FString UJsonParseLib::MakeJson(const TMap<FString, FString> Sources)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	for (TPair<FString, FString> Pair : Sources)
	{
		JsonObject->SetStringField(Pair.Key, Pair.Value);
	}

	FString json;
	TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&json);

	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	return json;
}

