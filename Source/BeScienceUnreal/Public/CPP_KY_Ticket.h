// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_KY_Ticket.generated.h"

UCLASS()
class BESCIENCEUNREAL_API ACPP_KY_Ticket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_KY_Ticket();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	class UCPP_KY_WG_TicketFront* WBP_TicketFront;
	class UUserWidget* WBP_TicketBack;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY ( EditDefaultsOnly , BlueprintReadWrite , Category = "Widget" )
	TSubclassOf<class UCPP_KY_WG_TicketFront> WBP_TicketFront_Class;

	UPROPERTY ( EditDefaultsOnly , BlueprintReadWrite , Category = "Widget" )
	TSubclassOf<class UUserWidget> WBP_TicketBack_Class;

	UPROPERTY ( EditDefaultsOnly , BlueprintReadWrite , Category = "Comp" )
	class UWidgetComponent* TicketFrontComp;
	UPROPERTY ( EditDefaultsOnly , BlueprintReadWrite , Category = "Comp" )
	class UWidgetComponent* TicketBackComp;

	UPROPERTY ( EditDefaultsOnly , BlueprintReadWrite , Category = "Comp" )
	class UBoxComponent* TicketBoxComp;

};
