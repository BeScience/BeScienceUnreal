// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicle/BSU_KartLocation.h"

// Sets default values
ABSU_KartLocation::ABSU_KartLocation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABSU_KartLocation::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABSU_KartLocation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

