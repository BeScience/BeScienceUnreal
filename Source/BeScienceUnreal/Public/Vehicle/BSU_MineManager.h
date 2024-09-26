// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BSU_MineManager.generated.h"

UCLASS()
class BESCIENCEUNREAL_API ABSU_MineManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABSU_MineManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 블루프린트에서 구현할 함수
	UFUNCTION(BlueprintImplementableEvent, Category = "MineManager")
	void SpawnMine();
};
