// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DocentActor.generated.h"

UCLASS()
class BESCIENCEUNREAL_API ADocentActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADocentActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public: 
	
	UPROPERTY(EditAnywhere)
	class USkeletalMesh* MeshComp;


	UPROPERTY(EditAnywhere)
	class USphereComponent* SphereComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString DocentName;

	
	
};
