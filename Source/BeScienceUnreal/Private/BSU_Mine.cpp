// Fill out your copyright notice in the Description page of Project Settings.


#include "BSU_Mine.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABSU_Mine::ABSU_Mine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	RootComponent = BoxComp;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(BoxComp);
}

// Called when the game starts or when spawned
void ABSU_Mine::BeginPlay()
{
	Super::BeginPlay();
	GenTime = 0;
}

// Called every frame
void ABSU_Mine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GenTime += DeltaTime;
	// 타겟 Actor가 있으면 따라간다.
	if (TargetActor)
	{
		// 타겟과의 거리
		if (FVector::Dist(TargetActor->GetActorLocation(), GetActorLocation()) > 70)
		{
			FVector TargetLoc = TargetActor->GetActorLocation();
			FVector dir = TargetLoc - GetActorLocation();
			dir.Normalize();
			FVector p0 = GetActorLocation();
			FVector p = p0 + Speed * dir * DeltaTime;
			SetActorLocation(p);
		}
	}
}

void ABSU_Mine::SetTarget(AActor* NewTargetActor, AController* target)
{
	TargetActor = NewTargetActor;
	bTargeted = true;
	TargetController = target;
}

