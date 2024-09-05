// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicle/BSU_VehiclePawn.h"
#include "Vehicle/BSU_VehicleWheelFront.h"
#include "Vehicle/BSU_VehicleWheelRear.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "BaseCharacter.h"
#include "Runtime/Engine/public/EngineUtils.h"
#include "Kyoulee/CPP_KY_PC_GamePlay.h"

ABSU_VehiclePawn::ABSU_VehiclePawn()
{
	// construct the front camera boom
	FrontSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Front Spring Arm"));
	FrontSpringArm->SetupAttachment(GetMesh());
	FrontSpringArm->TargetArmLength = 0.0f;
	FrontSpringArm->bDoCollisionTest = false;
	FrontSpringArm->bEnableCameraRotationLag = true;
	FrontSpringArm->CameraRotationLagSpeed = 15.0f;
	FrontSpringArm->SetRelativeLocation(FVector(30.0f, 0.0f, 120.0f));

	FrontCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Front Camera"));
	FrontCamera->SetupAttachment(FrontSpringArm);
	FrontCamera->bAutoActivate = false;

	// construct the back camera boom
	BackSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Back Spring Arm"));
	BackSpringArm->SetupAttachment(GetMesh());
	BackSpringArm->TargetArmLength = 650.0f;
	BackSpringArm->SocketOffset.Z = 150.0f;
	BackSpringArm->bDoCollisionTest = false;
	BackSpringArm->bInheritPitch = false;
	BackSpringArm->bInheritRoll = false;
	BackSpringArm->bEnableCameraRotationLag = true;
	BackSpringArm->CameraRotationLagSpeed = 2.0f;
	BackSpringArm->CameraLagMaxDistance = 50.0f;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetupAttachment(GetMesh());
	BoxComp->SetBoxExtent(FVector(300.0f, 200.0f, 100.0f));

	ArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComp"));
	ArrowComp->SetupAttachment(GetMesh());
	// (X=40.000000,Y=-170.000000,Z=60.000000)
	ArrowComp->SetRelativeLocation(FVector(40.0f, -200.0f, 60.0f));

	BackCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Back Camera"));
	BackCamera->SetupAttachment(BackSpringArm);

	// Configure the car mesh
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName(FName("Vehicle"));

	// get the Chaos Wheeled movement component
	ChaosVehicleMovement = CastChecked<UChaosWheeledVehicleMovementComponent>(GetVehicleMovement());

	// Set up the chassis
	GetChaosVehicleMovement()->ChassisHeight = 144.0f;
	GetChaosVehicleMovement()->DragCoefficient = 0.31f;

	// Set up the wheels
	GetChaosVehicleMovement()->bLegacyWheelFrictionPosition = true;
	GetChaosVehicleMovement()->WheelSetups.SetNum(4);

	GetChaosVehicleMovement()->WheelSetups[0].WheelClass = UBSU_VehicleWheelFront::StaticClass();
	GetChaosVehicleMovement()->WheelSetups[0].BoneName = FName("Phys_Wheel_FL");
	GetChaosVehicleMovement()->WheelSetups[0].AdditionalOffset = FVector(0.0f, 0.0f, 0.0f);

	GetChaosVehicleMovement()->WheelSetups[1].WheelClass = UBSU_VehicleWheelFront::StaticClass();
	GetChaosVehicleMovement()->WheelSetups[1].BoneName = FName("Phys_Wheel_FR");
	GetChaosVehicleMovement()->WheelSetups[1].AdditionalOffset = FVector(0.0f, 0.0f, 0.0f);

	GetChaosVehicleMovement()->WheelSetups[2].WheelClass = UBSU_VehicleWheelRear::StaticClass();
	GetChaosVehicleMovement()->WheelSetups[2].BoneName = FName("Phys_Wheel_BL");
	GetChaosVehicleMovement()->WheelSetups[2].AdditionalOffset = FVector(0.0f, 0.0f, 0.0f);

	GetChaosVehicleMovement()->WheelSetups[3].WheelClass = UBSU_VehicleWheelRear::StaticClass();
	GetChaosVehicleMovement()->WheelSetups[3].BoneName = FName("Phys_Wheel_BR");
	GetChaosVehicleMovement()->WheelSetups[3].AdditionalOffset = FVector(0.0f, 0.0f, 0.0f);

	// Set up the engine
	// NOTE: Check the Blueprint asset for the Torque Curve
	GetChaosVehicleMovement()->EngineSetup.MaxTorque = 500.0f;
	GetChaosVehicleMovement()->EngineSetup.MaxRPM = 5000.0f;
	GetChaosVehicleMovement()->EngineSetup.EngineIdleRPM = 900.0f;
	GetChaosVehicleMovement()->EngineSetup.EngineBrakeEffect = 0.2f;
	GetChaosVehicleMovement()->EngineSetup.EngineRevUpMOI = 5.0f;
	GetChaosVehicleMovement()->EngineSetup.EngineRevDownRate = 600.0f;

	// Set up the transmission
	GetChaosVehicleMovement()->TransmissionSetup.bUseAutomaticGears = true;
	GetChaosVehicleMovement()->TransmissionSetup.bUseAutoReverse = true;
	GetChaosVehicleMovement()->TransmissionSetup.FinalRatio = 2.81f;
	GetChaosVehicleMovement()->TransmissionSetup.ChangeUpRPM = 4000.0f;
	GetChaosVehicleMovement()->TransmissionSetup.ChangeDownRPM = 1500.0f;
	GetChaosVehicleMovement()->TransmissionSetup.GearChangeTime = 0.2f;
	GetChaosVehicleMovement()->TransmissionSetup.TransmissionEfficiency = 0.9f;

	GetChaosVehicleMovement()->TransmissionSetup.ForwardGearRatios.SetNum(5);
	GetChaosVehicleMovement()->TransmissionSetup.ForwardGearRatios[0] = 4.25f;
	GetChaosVehicleMovement()->TransmissionSetup.ForwardGearRatios[1] = 2.52f;
	GetChaosVehicleMovement()->TransmissionSetup.ForwardGearRatios[2] = 1.66f;
	GetChaosVehicleMovement()->TransmissionSetup.ForwardGearRatios[3] = 1.22f;
	GetChaosVehicleMovement()->TransmissionSetup.ForwardGearRatios[4] = 1.0f;

	GetChaosVehicleMovement()->TransmissionSetup.ReverseGearRatios.SetNum(1);
	GetChaosVehicleMovement()->TransmissionSetup.ReverseGearRatios[0] = 4.04f;

	// Set up the steering
	// NOTE: Check the Blueprint asset for the Steering Curve
	GetChaosVehicleMovement()->SteeringSetup.SteeringType = ESteeringType::Ackermann;
	GetChaosVehicleMovement()->SteeringSetup.AngleRatio = 0.7f;
}

void ABSU_VehiclePawn::BeginPlay()
{
	Super::BeginPlay();

}

void ABSU_VehiclePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 1. 컨트롤러를 가져와서 PlayerController인지 캐스팅 해본다.
	auto* pc = Cast<APlayerController>(Controller);
	// 2. 캐스팅 성공했다면 
	if (pc)
	{
		// 3. 그 객체를 이용해서 EnhancedInputLocalPlayerSubsystem을 가져온다.
		UEnhancedInputLocalPlayerSubsystem* subSys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
		// 4. SubSys를 이용해서 AddMappingContext를 한다.
		if (subSys)
		{
			subSys->AddMappingContext(IMC_Player, 1);
		}
	}
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// steering 
		EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Triggered, this, &ABSU_VehiclePawn::Steering);
		EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Completed, this, &ABSU_VehiclePawn::Steering);

		// throttle 
		EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Triggered, this, &ABSU_VehiclePawn::Throttle);
		EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Completed, this, &ABSU_VehiclePawn::Throttle);

		// break 
		EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Triggered, this, &ABSU_VehiclePawn::Brake);
		EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Started, this, &ABSU_VehiclePawn::StartBrake);
		EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Completed, this, &ABSU_VehiclePawn::StopBrake);

		// handbrake 
		EnhancedInputComponent->BindAction(HandbrakeAction, ETriggerEvent::Started, this, &ABSU_VehiclePawn::StartHandbrake);
		EnhancedInputComponent->BindAction(HandbrakeAction, ETriggerEvent::Completed, this, &ABSU_VehiclePawn::StopHandbrake);

		// look around 
		EnhancedInputComponent->BindAction(LookAroundAction, ETriggerEvent::Triggered, this, &ABSU_VehiclePawn::LookAround);

		// toggle camera 
		EnhancedInputComponent->BindAction(ToggleCameraAction, ETriggerEvent::Triggered, this, &ABSU_VehiclePawn::ToggleCamera);

		// reset the vehicle 
		EnhancedInputComponent->BindAction(ResetVehicleAction, ETriggerEvent::Triggered, this, &ABSU_VehiclePawn::ResetVehicle);

		// exit the vehicle
		EnhancedInputComponent->BindAction(ExitVehicleAction, ETriggerEvent::Triggered, this, &ABSU_VehiclePawn::ExitVehicle);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ABSU_VehiclePawn::Tick(float Delta)
{
	Super::Tick(Delta);

	// add some angular damping if the vehicle is in midair
	bool bMovingOnGround = ChaosVehicleMovement->IsMovingOnGround();
	GetMesh()->SetAngularDamping(bMovingOnGround ? 0.0f : 3.0f);

	// realign the camera yaw to face front
	float CameraYaw = BackSpringArm->GetRelativeRotation().Yaw;
	CameraYaw = FMath::FInterpTo(CameraYaw, 0.0f, Delta, 1.0f);

	BackSpringArm->SetRelativeRotation(FRotator(0.0f, CameraYaw, 0.0f));
	APlayerController* LocalPlayerController = GetWorld()->GetFirstPlayerController();

	if (LocalPlayerController != nullptr)
	{
		if (LocalPlayerController->GetPawn() == this)
			ChaosVehicleMovement->SetThrottleInput(0.5f);
	}
}

void ABSU_VehiclePawn::Steering(const FInputActionValue& Value)
{
	// get the input magnitude for steering
	float SteeringValue = Value.Get<float>();

	// add the input
	ChaosVehicleMovement->SetSteeringInput(SteeringValue);
}

void ABSU_VehiclePawn::CvSteering(const float Value)
{
	ChaosVehicleMovement->SetSteeringInput(Value);
}

void ABSU_VehiclePawn::Throttle(const FInputActionValue& Value)
{
	// get the input magnitude for the throttle
	float ThrottleValue = Value.Get<float>();

	// add the input
	ChaosVehicleMovement->SetThrottleInput(ThrottleValue);
}

void ABSU_VehiclePawn::Brake(const FInputActionValue& Value)
{
	// get the input magnitude for the brakes
	float BreakValue = Value.Get<float>();

	// add the input
	ChaosVehicleMovement->SetBrakeInput(BreakValue);
}

void ABSU_VehiclePawn::StartBrake(const FInputActionValue& Value)
{
	// call the Blueprint hook for the break lights
	BrakeLights(true);
}

void ABSU_VehiclePawn::StopBrake(const FInputActionValue& Value)
{
	// call the Blueprint hook for the break lights
	BrakeLights(false);

	// reset brake input to zero
	ChaosVehicleMovement->SetBrakeInput(0.0f);
}

void ABSU_VehiclePawn::StartHandbrake(const FInputActionValue& Value)
{
	// add the input
	ChaosVehicleMovement->SetHandbrakeInput(true);

	// call the Blueprint hook for the break lights
	BrakeLights(true);
}

void ABSU_VehiclePawn::StopHandbrake(const FInputActionValue& Value)
{
	// add the input
	ChaosVehicleMovement->SetHandbrakeInput(false);

	// call the Blueprint hook for the break lights
	BrakeLights(false);
}

void ABSU_VehiclePawn::LookAround(const FInputActionValue& Value)
{
	// get the flat angle value for the input 
	float LookValue = Value.Get<float>();

	// 카메라를 가져옴
	UCameraComponent* Camera = bFrontCameraActive ? FrontCamera : BackCamera;
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	APlayerCameraManager* CameraManager = PlayerController->PlayerCameraManager;
	FVector ViewLocation;
	FRotator ViewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(ViewLocation, ViewRotation);

	/*FMatrix ViewMatrix = FInverseRotationMatrix(ViewRotation) * FTranslationMatrix(-ViewLocation);
	FMatrix ProjectionMatrix = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCamera();
	FMatrix ViewProjectionMatrix = ViewMatrix * ProjectionMatrix;

	FConvexVolume ViewFrustum;
	GetViewFrustum(ViewProjectionMatrix, ViewFrustum);*/
	// add the input
	BackSpringArm->AddLocalRotation(FRotator(0.0f, LookValue, 0.0f));
}

void ABSU_VehiclePawn::ToggleCamera(const FInputActionValue& Value)
{
	// toggle the active camera flag
	bFrontCameraActive = !bFrontCameraActive;

	FrontCamera->SetActive(bFrontCameraActive);
	BackCamera->SetActive(!bFrontCameraActive);
}

void ABSU_VehiclePawn::ResetVehicle(const FInputActionValue& Value)
{
	// reset to a location slightly above our current one
	FVector ResetLocation = GetActorLocation() + FVector(0.0f, 0.0f, 50.0f);

	// reset to our yaw. Ignore pitch and roll
	FRotator ResetRotation = GetActorRotation();
	ResetRotation.Pitch = 0.0f;
	ResetRotation.Roll = 0.0f;

	// teleport the actor to the reset spot and reset physics
	SetActorTransform(FTransform(ResetRotation, ResetLocation, FVector::OneVector), false, nullptr, ETeleportType::TeleportPhysics);

	GetMesh()->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
	GetMesh()->SetPhysicsLinearVelocity(FVector::ZeroVector);

	UE_LOG(LogTemp, Error, TEXT("Reset Vehicle"));
}

void ABSU_VehiclePawn::ExitVehicle(const FInputActionValue& Value)
{
	// get the player controller

	UE_LOG(LogTemp, Warning, TEXT("ExitVehicle"));
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController != nullptr)
	{
		// unpossess the pawn
		//PlayerController->UnPossess();

		// AbaseCharacter를 찾아서 플레이어를 이동시킨다.
		for (TActorIterator<ABaseCharacter> ActorIterator(GetWorld()); ActorIterator; ++ActorIterator)
		{
			ABaseCharacter* Player = *ActorIterator;
			if (ActorIterator)
			{
				ActorIterator->ServerSetHidden(false);
				// Arrow 위치에 Player를 이동시킨다. (텔레포트)
				ActorIterator->SetActorTransform(ArrowComp->GetComponentTransform(), false, nullptr, ETeleportType::TeleportPhysics);
				UEnhancedInputLocalPlayerSubsystem* subSys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
				if (subSys)
				{
					subSys->RemoveMappingContext(IMC_Player);
				}

				//possess the player
				ACPP_KY_PC_GamePlay* pcgp = Cast<ACPP_KY_PC_GamePlay>(PlayerController);
				if (pcgp)
				{
					pcgp->ExitVehicle(Player);
				}

				TearDownOpencv();

				break;
			}
		}
	}
}

