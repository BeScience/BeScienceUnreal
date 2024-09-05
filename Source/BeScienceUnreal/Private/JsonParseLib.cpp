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
	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(json);
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject);
	if (FJsonSerializer::Deserialize(reader, result))
	{
		TArray<TSharedPtr<FJsonValue>> memoArray = result->GetArrayField(TEXT("memos"));
		for (TSharedPtr<FJsonValue> memoValue : memoArray)
		{
			TSharedPtr<FJsonObject> memoObject = memoValue->AsObject();
			FString Name = memoObject->GetStringField(TEXT("name"));
			FVector Pos;
			// "pos": "0.000000,0.000000,0.000000"
			FString PosString = memoObject->GetStringField(TEXT("pos"));
			TArray<FString> Parts;
			// Split the string using comma as a delimiter
			PosString.ParseIntoArray(Parts, TEXT(","), true);
			
			if (Parts.Num() == 3)  // Ensure that there are exactly 3 parts
			{
				FString X = Parts[0];
				FString Y = Parts[1];
				FString Z = Parts[2];

				Pos.X = FCString::Atof(*X);
				Pos.Y = FCString::Atof(*Y);
				Pos.Z = FCString::Atof(*Z);

				Memos.Add(TPair<FString, FVector>(Name, Pos));
			}
		}
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

