// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BSU_MemoBoard.generated.h"

UCLASS()
class BESCIENCEUNREAL_API ABSU_MemoBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABSU_MemoBoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnInteract();
	void AddMemo(const FVector& pos, const FString& str);
	void AddMemoRequest(const FVector& pos, const FString& str);
	void DeleteAllMemo();

	void OnMemoEdit(const FString& str);

	UFUNCTION(BlueprintCallable)
	void OnMemoEditEnd();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* MemoBoardMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UBoxComponent*> MemoBoardBoxs;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* RootComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* WidgetComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* ArrowComp;

	class UBSU_MemoHttpComponent* MemoHttpComp;

	virtual void NotifyActorOnClicked(FKey ButtonPressed) override;

	FVector MemoPos;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABSU_Memo> MemoFactory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UBSU_MemoEditWidget> MemoEditWidgetFactory;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBSU_MemoEditWidget* EditWidget;

	TArray<ABSU_Memo*> MemoArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* sound;
};
