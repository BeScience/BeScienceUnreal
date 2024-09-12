// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoBoard/BSU_MemoBoard.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/HitResult.h"
#include "MemoBoard/BSU_Memo.h"
#include "Components/ArrowComponent.h"
#include "MemoBoard/BSU_MemoEditWidget.h"
#include "MemoBoard/BSU_MemoHttpComponent.h"

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
	CameraComp->SetRelativeLocation(FVector(-0.000001, 200.000000, 110.000000));
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

	ArrowComp = CreateDefaultSubobject<UArrowComponent>(FName("ArrowComp"));
	ArrowComp->SetupAttachment(RootComp);
	// (Pitch=0.000000,Yaw=90.000000,Roll=-0.000000)
	ArrowComp->SetRelativeRotation(FRotator(0.000000, 90.000000, -0.000000));

	MemoHttpComp = CreateDefaultSubobject<UBSU_MemoHttpComponent>(FName("MemoHttpComp"));
}

// Called when the game starts or when spawned
void ABSU_MemoBoard::BeginPlay()
{
	Super::BeginPlay();

	EditWidget = CreateWidget<UBSU_MemoEditWidget>(GetWorld(), MemoEditWidgetFactory);
	EditWidget->OnAttachMemoDelegate.BindUObject(this, &ABSU_MemoBoard::OnMemoEdit);

	MemoHttpComp->ReqPostGetAllMemo();
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
	// local 좌표를 world 좌표로 변환
	FVector WorldPos = GetActorTransform().TransformPosition(pos);
	// ArrowComp 방향으로 살짝 앞으로 이동
	WorldPos += ArrowComp->GetForwardVector() * 2.0f;

	ABSU_Memo* Memo = GetWorld()->SpawnActor<ABSU_Memo>(MemoFactory, WorldPos, ArrowComp->GetComponentRotation());
	if (Memo)
	{
		Memo->SetMemoText(str);
	}

	MemoArray.Add(Memo);

	// 서버에 메모 추가
	MemoHttpComp->AttachMemo(str, pos);
}

void ABSU_MemoBoard::DeleteAllMemo()
{
	for (ABSU_Memo* Memo : MemoArray)
	{
		Memo->Destroy();
	}

	MemoArray.Empty();
}

void ABSU_MemoBoard::OnMemoEdit(const FString& str)
{
	EditWidget->RemoveFromViewport();
	AddMemo(MemoPos, str);
}

void ABSU_MemoBoard::OnMemoEditEnd()
{
	EditWidget->RemoveFromViewport();
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
				MemoPos = ActorTransform.InverseTransformPosition(ImpactPoint);
				
				EditWidget->AddToViewport();
				EditWidget->ShowMemoEditWidget();
				// AddMemo(LocalImpactPoint, "Hello");

				// 충돌한 컴포넌트
				UPrimitiveComponent* HitComponent = HitResult.GetComponent();

				UE_LOG(LogTemp, Log, TEXT("Hit Actor: %s"), *HitActor->GetName());
				UE_LOG(LogTemp, Log, TEXT("Impact Point: %s"), *ImpactPoint.ToString());
			}
		}
	}
}

