// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CPP_KY_TicketGate.generated.h"

UCLASS()
class BESCIENCEUNREAL_API ACPP_KY_TicketGate : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACPP_KY_TicketGate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UStaticMesh* GateMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY ( EditDefaultsOnly , BlueprintReadWrite , Category = "Component" )
	TSubclassOf<UStaticMesh> GateMeshClass;

	UPROPERTY ( EditDefaultsOnly , BlueprintReadWrite )
	UStaticMeshComponent* uGateComp;

	UPROPERTY ( EditDefaultsOnly , BlueprintReadWrite )
	class USphereComponent* uSphereComp;

	UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Door" )
	class ACPP_KY_Ticket_Door* TicketDoor;

	virtual void NotifyActorBeginOverlap ( AActor* OtherActor ) override;

	void BeginComponentOverlapGate ( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult );
};
