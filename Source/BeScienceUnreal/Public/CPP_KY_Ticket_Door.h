// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_KY_Ticket_Door.generated.h"

UCLASS()
class BESCIENCEUNREAL_API ACPP_KY_Ticket_Door : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_KY_Ticket_Door();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	TArray<AActor*> FreePassUserList;

	class UBoxComponent* uboxComp;

	UStaticMesh* DoorMesh_L;

	UStaticMesh* DoorMesh_R;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY ( EditDefaultsOnly , BlueprintReadWrite, Category="DoorState")
	float DoorBetweenSpace = 125;

	UPROPERTY ( EditDefaultsOnly , BlueprintReadWrite , Category = "SubClass" )
	TSubclassOf<UStaticMesh> DoorMeshClass_L;

	UPROPERTY ( EditDefaultsOnly , BlueprintReadWrite, Category = "SubClass" )
	TSubclassOf<UStaticMesh> DoorMeshClass_R;

	UPROPERTY ( EditDefaultsOnly , BlueprintReadWrite , Category = "Component" )
	UStaticMeshComponent* uDoorComp_L;

	UPROPERTY ( EditDefaultsOnly , BlueprintReadWrite , Category = "Component" )
	UStaticMeshComponent* uDoorComp_R;
	UFUNCTION()
	void AddFreePassUser ( AActor* user );

	UFUNCTION ()
	bool HasFreePassUser ( AActor* user );

	virtual void NotifyActorBeginOverlap ( AActor* OtherActor ) override;



	// door animation
	bool bDoorOpen = false;

	float doorbetween = 0;
	float Maxdoorbetween = 200;
	
	float currentDoorTime = 0;
	float maxDoorTime = 5;

	void DoorAnimation( float DeltaTime );

};
