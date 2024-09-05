// Fill out your copyright notice in the Description page of Project Settings.


#include "Kyoulee/CPP_KY_GrapElectrictyComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Vehicle/BSU_VehiclePawn.h"

// Sets default values for this component's properties
UCPP_KY_GrapElectrictyComponent::UCPP_KY_GrapElectrictyComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;

	// ...
}


// Called when the game starts
void UCPP_KY_GrapElectrictyComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
}


// Called every frame
void UCPP_KY_GrapElectrictyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCPP_KY_GrapElectrictyComponent::InitializeComponent()
{
	this->Owner= this->GetOwner();
	if (Owner->IsA<ACharacter>())
	{
		ACharacter* player = Cast<ACharacter>(this->Owner);
		if (player->bFindCameraComponentWhenViewTarget)
		{
			uPlayerCamera = player->GetComponentByClass<UCameraComponent>();
		}
	}
}

FMyStruct UCPP_KY_GrapElectrictyComponent::Grap()
{
	FMyStruct result;
	struct FHitResult OutHit;
	const FVector Start = this->Owner->GetActorLocation() + (this->GetForwardVector() * 100);
	const FVector End = this->Owner->GetActorLocation() + (this->GetForwardVector() * 1000);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this->Owner);
	bool hit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_GameTraceChannel2, Params);
	DrawDebugLine(GetWorld(), Start, End, hit ? FColor::Red : FColor::Blue, false, 1);
	if (hit )
	{
		if (OutHit.GetComponent()->ComponentTags.Find(FName("StickElectricty")))
		{
			result.isElactricty = true;
			result.HitComponent = OutHit.GetComponent();
			return result;
		}
	}
	result.isElactricty = false;
	result.HitComponent = OutHit.GetComponent();
	return result;
}

