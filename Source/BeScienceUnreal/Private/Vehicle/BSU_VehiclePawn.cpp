﻿// Fill out your copyright notice in the Description page of Project Settings.


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
#include "../../BeScienceUnreal.h"
#include "Vehicle/BSU_Star.h"
#include "UI/KartWidget.h"
#include "Kyoulee/CPP_KY_GS_GamePlay.h"
#include "Kyoulee/CPP_KY_GM_GamePlay.h"
#include "Kismet/GameplayStatics.h"
#include "BSU_Mine.h"
#include "Vehicle/BSU_Magnet.h"
#include "GameFramework/PlayerState.h"

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

	CollisionBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBoxComp"));
	CollisionBoxComp->SetupAttachment(GetMesh());
	CollisionBoxComp->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));

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
	GetChaosVehicleMovement()->SteeringSetup.AngleRatio = 1.0f;

}

void ABSU_VehiclePawn::BeginPlay()
{
	Super::BeginPlay();
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ABSU_VehiclePawn::OnMyBoxBeginOverlap);
	CollisionBoxComp->OnComponentBeginOverlap.AddDynamic(this, &ABSU_VehiclePawn::OnMyCollisionBoxBeginOverlap);

	if (MagnetCurve)
	{
		FOnTimelineFloat ProgressFunction;
		ProgressFunction.BindUFunction(this, FName("HandleProgress"));

		MagnetTimeline.AddInterpFloat(MagnetCurve, ProgressFunction);

		MagnetTimeline.SetLooping(false);
	}


	Mat = GetMesh()->CreateDynamicMaterialInstance(0);
	Mat->SetScalarParameterValue(TEXT("FresnelPercent"), 0);
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

		// ThrottleInput = 0.5f;
		// 위젯 설치
		if (IsLocallyControlled())
		{
			KartWidget = CreateWidget<UKartWidget>(GetWorld(), KartWidgetFactory);
			// 위젯을 화면에 표시
			if (KartWidget != nullptr)
			{
				KartWidget->AddToViewport();
			}
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

		// play the game
		EnhancedInputComponent->BindAction(PlayGameAction, ETriggerEvent::Triggered, this, &ABSU_VehiclePawn::ReadyGame);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ABSU_VehiclePawn::Tick(float Delta)
{
	Super::Tick(Delta);

	if (MagnetTimeline.IsPlaying())
	{
		MagnetTimeline.TickTimeline(Delta);
	}

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
			ChaosVehicleMovement->SetThrottleInput(ThrottleInput);
	}

	PrintNetLog();
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
			if (Player->IsHidden())
			{
				if (Player)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("ExitVehicle"));
					
					// Arrow 위치에 Player를 이동시킨다. (텔레포트)
					Player->SetActorTransform(ArrowComp->GetComponentTransform(), false, nullptr, ETeleportType::TeleportPhysics);
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
					if (KartWidget)
						KartWidget->RemoveFromParent();
					break;
				}
			}
		}
	}
}

void ABSU_VehiclePawn::ReadyGame(const FInputActionValue& Value)
{
	// 방장일 경우
	if (HasAuthority())
	{
		if (nullptr == GameState) GameState = GetWorld()->GetGameState<ACPP_KY_GS_GamePlay>();
		// 게임스테이트에게 게임 시작을 알린다.
		if (GameState && GameState->GamePlayState == EGamePlayState::EWaiting)
		{
			GameState->SetGamePlayState(EGamePlayState::EReady);
		}

		// 멀티케스팅으로 게임시작을 알린다.
		// 게임모드를 가져온다.
		AGameModeBase* gamMode = UGameplayStatics::GetGameMode(GetWorld());
		ACPP_KY_GM_GamePlay* gm = Cast<ACPP_KY_GM_GamePlay>(gamMode);
		if (gm)
			gm->TeleportAllPlayersToSpawn();
	}
}

void ABSU_VehiclePawn::StartGame()
{
	/*USkeletalMeshComponent* vehicleMesh = GetMesh();
	vehicleMesh->SetSimulatePhysics(true);*/

	ThrottleInput = 0.5f;
	if (HasAuthority())
	{
		if (nullptr == GameState) GameState = GetWorld()->GetGameState<ACPP_KY_GS_GamePlay>();
		// 게임스테이트에게 게임 시작을 알린다.
		if (GameState)
		{
			// GameState->SetGamePlayState(EGamePlayState::EPlaying);

			AGameModeBase* gamMode = UGameplayStatics::GetGameMode(GetWorld());
			ACPP_KY_GM_GamePlay* gm = Cast<ACPP_KY_GM_GamePlay>(gamMode);
			if (gm)
				gm->StartGameTime();
		}
	}
}

void ABSU_VehiclePawn::ClientReadyGame()
{
	if (IsLocallyControlled())
	{
		KartWidget->ShowStartText(false);

		// State 변경
		// 각 유저 차량 위치 변경
		KartWidget->ShowPlayGame();
	}

	ThrottleInput = 0.0f;
	// 게임스테이트 가져오기
	if (nullptr == GameState) GameState = GetWorld()->GetGameState<ACPP_KY_GS_GamePlay>();
}

void ABSU_VehiclePawn::ResultGame(bool bWin)
{
	// 자신의 마인을 모두 제거한다.
	for (auto& ConnectedMine : ConnectedMines)
	{
		ConnectedMine->Destroy();
	}

	ConnectedMines.Empty();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController->IsLocalController() && KartWidget)
	{
		if (bWin)
		{
			KartWidget->ShowWin();
		}
		else
		{
			KartWidget->ShowLose();
		}
	}

	if (HasAuthority())
	{
		auto* ps = GetPlayerState();
		ps->SetScore(0);
	}
}

void ABSU_VehiclePawn::SetTimer(int32 GameTime)
{
	if (KartWidget)
		KartWidget->SetGameTime(GameTime);
}

void ABSU_VehiclePawn::ShrinkBox()
{
	BoxComp->SetBoxExtent(OldBoxExtent);
}

void ABSU_VehiclePawn::HandleProgress(float Value)
{
	Mat->SetScalarParameterValue(TEXT("FresnelPercent"), Value);
}

void ABSU_VehiclePawn::OnMyBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	// 컨트롤러가 없다면 무시
	if (! IsRiding)
		return;

	// Game State를 가져온다.
	if (nullptr == GameState) GameState = GetWorld()->GetGameState<ACPP_KY_GS_GamePlay>();
	if (GameState && GameState->GamePlayState != EGamePlayState::EPlaying)
		return;

	ABSU_Star* star = Cast<ABSU_Star>(OtherActor);
	if (star)
	{
		if (!star->bTargeted)
		{
			UE_LOG(LogTemp, Warning, TEXT("OnBoxBeginOverlap"));
			
			// mine생성
			ABSU_Mine* NewMine;
			
			if (IsLocallyControlled())
			{
				NewMine = GetWorld()->SpawnActor<ABSU_Mine>(MineFactory, GetActorLocation(), FRotator::ZeroRotator);
			}
			else
			{
				NewMine = GetWorld()->SpawnActor<ABSU_Mine>(EnemyMineFactory, GetActorLocation(), FRotator::ZeroRotator);
			}

			NewMine->SetTarget(this, GetController());
			if (ConnectedMines.Num() > 0)
			{
				if (ConnectedMines[0] == nullptr)
				{
					int a = 0;
				}
				ConnectedMines[0]->SetTarget(NewMine, GetController());
			}

			star->SetTarget(this);
			ConnectedMines.EmplaceAt(0, NewMine);

			auto* ps = GetPlayerState();
			if (ps)
				ps->SetScore(ps->GetScore() + 1);
		}
	}

	//if (OtherActor != nullptr && OtherActor->IsA(ABSU_Magnet::StaticClass()))
	{
		ABSU_Magnet* magnet = Cast<ABSU_Magnet>(OtherActor);
		if (magnet)
		{
			UE_LOG(LogTemp, Warning, TEXT("Magnet"));

			// 마그넷을 먹었을 때 박스가 커진다.
			// 이전 박스크기를 저장한다.
			BoxComp->SetBoxExtent(FVector(1000.0f, 1000.0f, 200.0f));
			// 5초후 작아진다.

			MagnetTimeline.PlayFromStart();
			magnet->SetTarget(this);
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABSU_VehiclePawn::ShrinkBox, 5.0f, false);
		}
	}
}

void ABSU_VehiclePawn::OnMyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 컨트롤러가 없다면 무시
	if (!IsRiding)
		return;

	// Game State를 가져온다.
	if (nullptr == GameState) GameState = GetWorld()->GetGameState<ACPP_KY_GS_GamePlay>();
	if (GameState && GameState->GamePlayState != EGamePlayState::EPlaying)
		return;

	ABSU_Mine* mine = Cast<ABSU_Mine>(OtherActor);
	if (mine && mine->GenTime > 1)
	{
		if (mine->TargetController != GetController())
		{
			// 자신의 마인을 모두 제거한다.
			for (auto& ConnectedMine : ConnectedMines)
			{
				ConnectedMine->Destroy();
			}

			// 이펙트 생성
			if (ExplosionEffect)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
			}

			if (sound)
			{
				UGameplayStatics::PlaySound2D(GetWorld(), sound);
			}

			ConnectedMines.Empty();
			if (HasAuthority())
			{
				auto* ps = GetPlayerState();
				ps->SetScore(0);
			}
		}
	}
}

void ABSU_VehiclePawn::PrintNetLog()
{
// 	const FString& name = GetNetConnection() != nullptr ? TEXT("Valid Connection") : TEXT("Invalid Connection");
// 	const FString& onwerName = GetOwner() != nullptr ? GetOwner()->GetName() : TEXT("No Owner");
// 
// 	const FString logStr = FString::Printf(TEXT("Net Connection : %s\nOwnerName : %s\n LocalRole : %s \n RemoteRole : %s "), *name, *onwerName, *LOCALROLE, *REMOTEROLE);
// 
// 	DrawDebugString(GetWorld(), GetActorLocation() + FVector::UpVector * 100, logStr, 0, FColor::Red, 0.0f, true, 1);
}
