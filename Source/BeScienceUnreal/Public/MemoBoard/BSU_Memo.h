// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BSU_Memo.generated.h"

UCLASS()
class BESCIENCEUNREAL_API ABSU_Memo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABSU_Memo();

	void SetMemoText(FString Text);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USceneComponent* SceneComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* MeshComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UWidgetComponent* WidgetComp;
};
