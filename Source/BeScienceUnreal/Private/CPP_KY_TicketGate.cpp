// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_KY_TicketGate.h"
#include "CPP_KY_Ticket_Door.h"
#include "Components/SphereComponent.h"
#include <CPP_KY_Ticket.h>

// Sets default values
ACPP_KY_TicketGate::ACPP_KY_TicketGate()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->uSphereComp = CreateDefaultSubobject<USphereComponent> (FName("uSphereComp"));
	this->uSphereComp->SetSphereRadius(300);
	this->SetRootComponent ( this->uSphereComp );

	this->uGateComp = CreateDefaultSubobject<UStaticMeshComponent> ( FName ( "uGateComp" ) );
	this->uGateComp->SetupAttachment ( this->uSphereComp );

	if (this->GateMeshClass)
	{
		this->GateMesh = NewObject<UStaticMesh> ( this->GateMeshClass );
		this->uGateComp->SetStaticMesh ( this->GateMesh );
	}
}

// Called when the game starts or when spawned
void ACPP_KY_TicketGate::BeginPlay()
{
	Super::BeginPlay();

	//this->uSphereComp->OnComponentBeginOverlap.AddDynamic( this , &ACPP_KY_TicketGate::BeginComponentOverlapGate );
}

// Called every frame
void ACPP_KY_TicketGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPP_KY_TicketGate::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACPP_KY_TicketGate::NotifyActorBeginOverlap ( AActor* OtherActor )
{


	UE_LOG ( LogTemp , Display , TEXT ( "NotifyActorBeginOverlap : overlap something" ) );

	AActor* overlapActor = OtherActor;
	if (overlapActor->IsA< ACPP_KY_Ticket> ())
	{
		//ticketcomponet need;
		ACPP_KY_Ticket* ticket = Cast<ACPP_KY_Ticket> ( overlapActor );
		AActor* ticketuser = ticket->GetTicketUser ();
		if (this->TicketDoor)
			this->TicketDoor->AddFreePassUser ( ticketuser );
	}

}

void ACPP_KY_TicketGate::BeginComponentOverlapGate ( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult )
{
	UE_LOG ( LogTemp , Display , TEXT ( "overlap something" ) );
}

