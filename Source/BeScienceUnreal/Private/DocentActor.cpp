// Fill out your copyright notice in the Description page of Project Settings.


#include "DocentActor.h"
#include "Engine/SkeletalMesh.h"

// Sets default values
ADocentActor::ADocentActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void ADocentActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADocentActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

