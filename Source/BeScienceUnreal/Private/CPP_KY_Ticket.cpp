// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_KY_Ticket.h"
#include "CPP_KY_WG_TicketFront.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
// Sets default values
ACPP_KY_Ticket::ACPP_KY_Ticket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->TicketBoxComp = CreateDefaultSubobject<UBoxComponent> ( FName ( "TicketBoxComp" ) );
	this->TicketBoxComp->SetupAttachment ( this->GetRootComponent () );
	this->TicketBoxComp->SetBoxExtent ( FVector ( 0.1, 30 , 40) );


	this->TicketFrontComp = CreateDefaultSubobject<UWidgetComponent> ( FName ( "TicketFrontComp" ) );
	this->TicketFrontComp->SetupAttachment ( TicketBoxComp );
	this->TicketFrontComp->SetRelativeLocation ( FVector ( 0.1 , 0 , 0 ) );
	this->TicketFrontComp->SetRelativeScale3D ( FVector ( 0.5, 0.5, 0.5 ) );
	this->TicketFrontComp->SetDrawSize ( FVector2D ( 120 , 160 ) );
	this->TicketFrontComp->SetCollisionEnabled ( ECollisionEnabled::NoCollision );

	ConstructorHelpers::FClassFinder<UCPP_KY_WG_TicketFront> tempWBPFront (TEXT( "/Script/UMGEditor.WidgetBlueprint'/Game/Kyoulee/WidGets/Ticket/WBP_Ticket_Front.WBP_Ticket_Front_C'" ));

	if (tempWBPFront.Succeeded())
	{
		this->WBP_TicketFront_Class = tempWBPFront.Class;
		this->TicketFrontComp->SetWidgetClass( WBP_TicketFront_Class );
	}

	this->TicketBackComp = CreateDefaultSubobject<UWidgetComponent> ( FName ( "TicketBackComp" ) );
	this->TicketBackComp->SetupAttachment ( TicketBoxComp );
	this->TicketBackComp->SetRelativeScale3D ( FVector ( 0.5 , 0.5 , 0.5 ) );
	this->TicketBackComp->SetRelativeLocation ( FVector ( -0.1 , 0 , 0 ) );
	this->TicketBackComp->SetRelativeRotation ( FRotator ( 0 , 180 , 0 ) );
	this->TicketBackComp->SetDrawSize ( FVector2D ( 120 , 160 ) );
	this->TicketBackComp->SetCollisionEnabled ( ECollisionEnabled::NoCollision );

	ConstructorHelpers::FClassFinder<UUserWidget> tempWBPBack ( TEXT ( "/Script/UMGEditor.WidgetBlueprint'/Game/Kyoulee/WidGets/Ticket/WBP_Ticket_Back.WBP_Ticket_Back_C'"));

	if (tempWBPBack.Succeeded())
	{
		this->WBP_TicketBack_Class = tempWBPBack.Class;
		this->TicketBackComp->SetWidgetClass ( WBP_TicketBack_Class );
	}
}

// Called when the game starts or when spawned
void ACPP_KY_Ticket::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_KY_Ticket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

