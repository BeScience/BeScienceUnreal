// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicle/BSU_Star.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABSU_Star::ABSU_Star()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	RootComponent = BoxComp;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(BoxComp);
}

// Called when the game starts or when spawned
void ABSU_Star::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABSU_Star::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 타겟 Actor가 있으면 따라간다.
	if (TargetActor)
	{
		// 타겟과의 거리
		if (FVector::Dist(TargetActor->GetActorLocation(), GetActorLocation()) > 80)
		{
			FVector TargetLoc = TargetActor->GetActorLocation();
			FVector dir = TargetLoc - GetActorLocation();
			dir.Normalize();
			FVector p0 = GetActorLocation();
			FVector p =  p0 + Speed * dir * DeltaTime;
			SetActorLocation(p);
		}
		else
		{
			// 타겟에 도달하면 파괴
			Destroy();
		}
	}
}

void ABSU_Star::SetTarget(AActor* NewTargetActor)
{
	TargetActor = NewTargetActor;
	bTargeted = true;
}

