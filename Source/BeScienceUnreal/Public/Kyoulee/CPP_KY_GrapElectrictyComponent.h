// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPP_KY_GrapElectrictyComponent.generated.h"

USTRUCT(BlueprintType)
struct FMyStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	bool isElactricty;

	UPROPERTY(EditAnywhere)
	UPrimitiveComponent* HitComponent;
	

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BESCIENCEUNREAL_API UCPP_KY_GrapElectrictyComponent : public UPrimitiveComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCPP_KY_GrapElectrictyComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	AActor* Owner;
	class UBoxComponent* box;
	class UCameraComponent* uPlayerCamera;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void PrintNetLog();

	virtual void InitializeComponent() override;

	UFUNCTION(BlueprintCallable)
		FMyStruct Grap();
};

