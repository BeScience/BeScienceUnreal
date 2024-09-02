// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPP_KY_Ticket_Player_Component.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BESCIENCEUNREAL_API UCPP_KY_Ticket_Player_Component : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCPP_KY_Ticket_Player_Component();

protected:
	virtual void InitializeComponent () override;
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame

	UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Ticket" )
	TSubclassOf<class ACPP_KY_Ticket> aTicketClass;

private:
	AActor* Owner;
	class USphereComponent* uSphereComp;
	
	class ACPP_KY_Ticket* aTicket;

};
