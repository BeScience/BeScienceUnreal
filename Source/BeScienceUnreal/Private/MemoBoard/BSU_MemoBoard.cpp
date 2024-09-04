// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoBoard/BSU_MemoBoard.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/HitResult.h"

// Sets default values
ABSU_MemoBoard::ABSU_MemoBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(FName("RootComp"));
	RootComponent = RootComp;

	MemoBoardMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("MemoBoardMesh"));
	MemoBoardMesh->SetupAttachment(RootComp);
	// (X = 0.000000, Y = 0.000000, Z = 110.000000)
	MemoBoardMesh->SetRelativeLocation(FVector(0.000000, 0.000000, 110.000000));
	MemoBoardMesh->SetRelativeScale3D(FVector(3.000000, 0.100000, 2.000000));

	CameraComp = CreateDefaultSubobject<UCameraComponent>(FName("CameraComp"));
	CameraComp->SetupAttachment(RootComp);
	// (X=-0.000001,Y=2410.000000,Z=0.000000)
	CameraComp->SetRelativeLocation(FVector(-0.000001, 2410.000000, 0.000000));
	// (Pitch=0.000000,Yaw=-89.999999,Roll=0.000000)
	CameraComp->SetRelativeRotation(FRotator(0.000000, -89.999999, 0.000000));

	BoxComp = CreateDefaultSubobject<UBoxComponent>(FName("BoxComp"));
	BoxComp->SetupAttachment(RootComp);
	BoxComp->SetRelativeLocation(FVector(0, 150, 0));
	BoxComp->SetBoxExtent(FVector(150, 150, 50));

	WidgetComp = CreateDefaultSubobject<UWidgetComponent>(FName("WidgetComp"));
	WidgetComp->SetupAttachment(RootComp);
	// (X=0.000000,Y=0.000000,Z=-36.500000)
	WidgetComp->SetRelativeLocation(FVector(0.000000, 0.000000, -36.500000));
	// (Pitch=0.000000,Yaw=89.999999,Roll=0.000000)
	WidgetComp->SetRelativeRotation(FRotator(0.000000, 89.999999, 0.000000));
	// (X=0.333333,Y=10.000000,Z=0.500000)
	WidgetComp->SetRelativeScale3D(FVector(0.333333, 10.000000, 0.500000));
}

// Called when the game starts or when spawned
void ABSU_MemoBoard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABSU_MemoBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABSU_MemoBoard::AddMemo(const FVector& pos, const FString& str)
{
	// 좌표에 메모 스폰함.
	//GetWorld()->SpawnActor()
}

void ABSU_MemoBoard::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);

	// 마우스 좌표 가져옴
	//float MousePosX;
	//float MousePosY;
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		FHitResult HitResult;
		// ECC_Visibility는 해당 라인 트레이스가 감지할 채널을 지정합니다.
		if (PC->GetHitResultUnderCursor(ECC_Visibility, true, HitResult))
		{
			// 라인 트레이스가 맞은 오브젝트가 있다면 처리
			if (HitResult.bBlockingHit)
			{
				// HitResult를 통해 다양한 정보를 얻을 수 있습니다.
				// 충돌한 위치의 좌표
				FVector ImpactPoint = HitResult.ImpactPoint;
				// 충돌한 액터
				AActor* HitActor = HitResult.GetActor();

				// 액터의 트랜스폼을 가져옵니다.
				FTransform ActorTransform = HitActor->GetActorTransform();

				// 월드 좌표를 로컬 좌표로 변환합니다.
				FVector LocalImpactPoint = ActorTransform.InverseTransformPosition(ImpactPoint);

				AddMemo(LocalImpactPoint, "Hello");

				// 충돌한 컴포넌트
				UPrimitiveComponent* HitComponent = HitResult.GetComponent();

				UE_LOG(LogTemp, Log, TEXT("Hit Actor: %s"), *HitActor->GetName());
				UE_LOG(LogTemp, Log, TEXT("Impact Point: %s"), *ImpactPoint.ToString());
			}
		}
	}
}

