// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "Vehicle/BSU_VehiclePawn.h"
#include "MemoBoard/BSU_MemoBoard.h"
#include "Kyoulee/CPP_KY_PC_GamePlay.h"
#include "Net/UnrealNetwork.h"
#include "../BeScienceUnreal.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent> ( TEXT ( "SpringArmComp" ) );
	SpringArmComp->SetupAttachment ( RootComponent );
	SpringArmComp->SetRelativeLocation ( FVector ( 0 , 40 , 80 ) );
	SpringArmComp->TargetArmLength = 200;

	CameraComp = CreateDefaultSubobject<UCameraComponent> ( TEXT ( "CameraComp" ) );
	CameraComp->SetupAttachment ( SpringArmComp );

	ConstructorHelpers::FObjectFinder<USkeletalMesh>TempMesh ( TEXT ( "/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Quinn.SKM_Quinn'" ) );

	if (TempMesh.Succeeded ())
	{
		GetMesh ()->SetSkeletalMesh ( TempMesh.Object );
		GetMesh ()->SetRelativeLocationAndRotation ( FVector ( 0 , 0 , -90 ) , FRotator ( 0 , 90 , 0 ) );
	}


}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FTransform ttt = FTransform ( GetControlRotation () );
	Direction = ttt.TransformVector ( Direction );
	Direction.Z = 0;
	Direction.Normalize ();
	AddMovementInput ( Direction , 1 );
	Direction = FVector::ZeroVector;


	PrintNetLog();
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto* pc = Cast<APlayerController>(Controller);
	if (pc)
	{
		UEnhancedInputLocalPlayerSubsystem* subSys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
		if (subSys)
		{
			subSys->AddMappingContext(imc_Base, 0);
		}
	}

	UEnhancedInputComponent* input = CastChecked<UEnhancedInputComponent> ( PlayerInputComponent );

	if (input)
	{
		input->BindAction ( ia_Move , ETriggerEvent::Triggered , this , &ABaseCharacter::OnMyActionMove );
		input->BindAction ( ia_Look , ETriggerEvent::Triggered , this , &ABaseCharacter::OnMyActionLook );
		input->BindAction ( ia_Jump , ETriggerEvent::Started , this , &ABaseCharacter::OnMyActionJump );
		input->BindAction(ia_Function, ETriggerEvent::Started, this, &ABaseCharacter::OnMyActionFunction);
	}

}

void ABaseCharacter::OnMyActionMove ( const FInputActionValue& inputValue )
{

	FVector2D v = inputValue.Get<FVector2D> ();
	Direction.X = v.X;
	Direction.Y = v.Y;
	Direction.Normalize ();


}

void ABaseCharacter::OnMyActionLook ( const FInputActionValue& inputValue )
{

	FVector2D v = inputValue.Get<FVector2D> ();

	AddControllerPitchInput ( v.Y );
	AddControllerYawInput ( v.X );
}

void ABaseCharacter::OnMyActionJump ( const FInputActionValue& inputValue )
{
	Jump ();

}

void ABaseCharacter::OnMyActionFunction(const FInputActionValue& inputValue)
{
	UE_LOG(LogTemp, Warning, TEXT("OnMyActionFunction"));
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors, TSubclassOf<AActor>());
	for (AActor* Actor : OverlappingActors)
	{
		ABSU_VehiclePawn* pawn = Cast<ABSU_VehiclePawn>(Actor);
		if (pawn)
		{
			// possess
			APlayerController* pc = GetWorld()->GetFirstPlayerController();
			if (pc)
			{
				UEnhancedInputLocalPlayerSubsystem* subSys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
				if (subSys)
				{
					subSys->RemoveMappingContext(pawn->IMC_Player);
				}

				ServerSetHidden(true);
				ACPP_KY_PC_GamePlay* pcgp = Cast<ACPP_KY_PC_GamePlay>(pc);
				if (pcgp)
				{
					pcgp->EnterVehicle(pawn);
				}

				pawn->SetupOpencv();
			}
		}

		ABSU_MemoBoard* board = Cast<ABSU_MemoBoard>(Actor);
		if (board)
		{
			// board
			// 숨기기
			SetActorHiddenInGame(true);
			board->OnInteract();
		}
	}
}

void ABaseCharacter::CameraMoveMent()
{
}

void ABaseCharacter::MoveCamera()
{
}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// bIsHidden 변수를 복제 설정
	DOREPLIFETIME(ABaseCharacter, bIsHidden);
}

void ABaseCharacter::OnRep_HiddenState()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("OnRep_HiddenState"));
	SetActorHiddenInGame(bIsHidden);
}

void ABaseCharacter::ServerSetHidden_Implementation(bool bPlayerHidden)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("ServerSetHidden_Implementation"));
	// 서버에서 상태를 설정하고 이를 클라이언트로 전파
	bIsHidden = bPlayerHidden;

	// 서버에서도 직접 SetActorHiddenInGame을 호출
	SetActorHiddenInGame(bIsHidden);
}

bool ABaseCharacter::ServerSetHidden_Validate(bool bPlayerHidden)
{
	return true;
}

void ABaseCharacter::SetHidden(bool bPlayerHidden)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("SetHidden"));
	// 클라이언트에서 상태를 설정하고 이를 서버로 전파
	ServerSetHidden(bPlayerHidden);
}

void ABaseCharacter::PrintNetLog()
{
// 	const FString& name = GetNetConnection() != nullptr ? TEXT("Valid Connection") : TEXT("Invalid Connection");
// 	const FString& onwerName = GetOwner() != nullptr ? GetOwner()->GetName() : TEXT("No Owner");
// 
// 	const FString logStr = FString::Printf(TEXT("Net Connection : %s\nOwnerName : %s\n LocalRole : %s \n RemoteRole : %s "), *name, *onwerName, *LOCALROLE, *REMOTEROLE);

// 	DrawDebugString(GetWorld(), GetActorLocation() + FVector::UpVector * 100, logStr, 0, FColor::Red, 0.0f, true, 1);

}
