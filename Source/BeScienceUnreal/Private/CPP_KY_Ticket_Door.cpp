// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_KY_Ticket_Door.h"
#include "Components/BoxComponent.h"

// Sets default values
ACPP_KY_Ticket_Door::ACPP_KY_Ticket_Door()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->uboxComp = CreateDefaultSubobject<UBoxComponent> ( FName ( "uboxComp" ) );
	this->uboxComp->SetBoxExtent (FVector(200, 300, 400));
	this->SetRootComponent ( this->uboxComp );

	this->uDoorComp_L = CreateDefaultSubobject<UStaticMeshComponent> ( FName ( "uDoorComp_L" ) );
	this->uDoorComp_L->SetupAttachment ( this->uboxComp );
	this->uDoorComp_L->SetRelativeLocation ( FVector(0, -DoorBetweenSpace , 0) );

	this->uDoorComp_R = CreateDefaultSubobject<UStaticMeshComponent> ( FName ( "uDoorComp_R" ) );
	this->uDoorComp_R->SetupAttachment ( this->uboxComp );
	this->uDoorComp_R->SetRelativeLocation ( FVector ( 0 , DoorBetweenSpace , 0 ) );

	if (this->DoorMeshClass_L)
	{
		this->DoorMesh_L = NewObject<UStaticMesh>( this->DoorMeshClass_L );
		this->uDoorComp_L->SetStaticMesh ( DoorMesh_L );
	}

	if (this->DoorMeshClass_R)
	{
		this->DoorMesh_R = NewObject<UStaticMesh> ( this->DoorMeshClass_R );
		this->uDoorComp_R->SetStaticMesh ( DoorMesh_R );
	}
}

// Called when the game starts or when spawned
void ACPP_KY_Ticket_Door::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACPP_KY_Ticket_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (currentDoorTime < 0)
		this->bDoorOpen = false;
	if (bDoorOpen)
		currentDoorTime -= DeltaTime;
	DoorAnimation(DeltaTime);
}

void ACPP_KY_Ticket_Door::AddFreePassUser ( AActor* user )
{
	this->FreePassUserList.Add ( user );
}

bool ACPP_KY_Ticket_Door::HasFreePassUser ( AActor* user )
{
	if (-1 == this->FreePassUserList.Find ( user ))
		return false;
	return true;
}

void ACPP_KY_Ticket_Door::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (HasFreePassUser(OtherActor))
	{
		UE_LOG(LogTemp, Display, TEXT("door open"));
		currentDoorTime = 5;
	}
}

void ACPP_KY_Ticket_Door::DoorAnimation(float DeltaTime)
{
	if (bDoorOpen)
	{
		FVector doormove_L = uDoorComp_L->GetRelativeLocation() + (uDoorComp_L->GetRightVector() * DeltaTime * 1000);
		FVector doormove_R = uDoorComp_R->GetRelativeLocation() - (uDoorComp_R->GetRightVector() * DeltaTime * 1000);
		if (Maxdoorbetween > doormove_L.Length())
		{
			uDoorComp_L->SetRelativeLocation(doormove_L);
			uDoorComp_R->SetRelativeLocation(doormove_R);
		}
		else {
			this->bDoorOpen = true;
		}
	}
	else
	{
		FVector doormove_L = uDoorComp_L->GetRelativeLocation() - (uDoorComp_L->GetRightVector() * DeltaTime * 1000);
		FVector doormove_R = uDoorComp_R->GetRelativeLocation() + (uDoorComp_R->GetRightVector() * DeltaTime * 1000);
		if (100 < doormove_L.Length())
		{
			uDoorComp_L->SetRelativeLocation(doormove_L);
			uDoorComp_R->SetRelativeLocation(doormove_R);
		}
	}
}


// 문 움직임 애니메이션으로 할것인가 로직으로 할것인가?
