// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BSU_Magnet.generated.h"

UCLASS()
class BESCIENCEUNREAL_API ABSU_Magnet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABSU_Magnet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// static mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* MeshComp;

	// BoxComp
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* BoxComp;

	// Target Actor
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AActor* TargetActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Speed = 3000;

public:
	void SetTarget(AActor* NewTargetActor);

	bool bTargeted = false;
};
