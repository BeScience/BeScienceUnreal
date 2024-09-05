// Fill out your copyright notice in the Description page of Project Settings.


#include "Kyoulee/CPP_KY_API_Core.h"
#include "Kyoulee/CPP_KY_API_BaseComponent.h"

// Sets default values
ACPP_KY_API_Core::ACPP_KY_API_Core()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	this->API_BaseComp = CreateDefaultSubobject<UCPP_KY_API_BaseComponent> (FName("API_BaseComp"));
}

// Called when the game starts or when spawned
void ACPP_KY_API_Core::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* playerController = this->GetWorld ()->GetFirstPlayerController ();
	this->EnableInput( playerController );
	
}

// Called every frame
void ACPP_KY_API_Core::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPP_KY_API_Core::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (this->API_BaseComp)
	{
		this->API_BaseComp->AddPlayerInputComponent (PlayerInputComponent);
	}
}

