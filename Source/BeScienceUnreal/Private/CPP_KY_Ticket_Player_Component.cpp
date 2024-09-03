// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_KY_Ticket_Player_Component.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "CPP_KY_Ticket.h"

// Sets default values for this component's properties
UCPP_KY_Ticket_Player_Component::UCPP_KY_Ticket_Player_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	// ...;

	this->uSphereComp = CreateDefaultSubobject<USphereComponent> ("UShapeComp");
	this->uSphereComp->SetSphereRadius(100);

}



void UCPP_KY_Ticket_Player_Component::InitializeComponent ()
{
	Super::InitializeComponent ();

	this->Owner = this->GetOwner ();

	if (this->aTicketClass) {
		this->aTicket = GetWorld()->SpawnActor<ACPP_KY_Ticket>(this->aTicketClass, this->Owner->GetActorLocation() , this->Owner->GetActorRotation());
		this->aTicket->SetTicketUser (this->Owner);
		if (this->Owner->IsA<ACharacter> ())
		{
			ACharacter* OwnerCharacter = Cast<ACharacter> ( this->Owner );
			this->aTicket->AttachToComponent ( OwnerCharacter->GetMesh() , FAttachmentTransformRules::KeepRelativeTransform , FName ("ik_hand_gun"));
		}
		else
		{
			this->aTicket->AttachToComponent ( this->Owner->GetRootComponent () , FAttachmentTransformRules::KeepRelativeTransform );
		}
	}

}
// Called when the game starts
void UCPP_KY_Ticket_Player_Component::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


