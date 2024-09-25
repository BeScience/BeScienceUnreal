// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicle/BSU_StarLocation.h"

// Sets default values
ABSU_StarLocation::ABSU_StarLocation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABSU_StarLocation::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABSU_StarLocation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

