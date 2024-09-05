// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoBoard/BSU_Memo.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "MemoBoard/BSU_MemoWidget.h"

// Sets default values
ABSU_Memo::ABSU_Memo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(SceneComp);
	//(Pitch=-90.000000,Yaw=0.000000,Roll=0.000000)
	MeshComp->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));


	WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComp"));
	WidgetComp->SetupAttachment(SceneComp);

	ConstructorHelpers::FClassFinder<UUserWidget> TempWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Swkim/UI/WBP_Memo.WBP_Memo_C'"));
	if (TempWidget.Succeeded())
	{
		WidgetComp->SetWidgetClass(TempWidget.Class);
		WidgetComp->SetDrawSize(FVector2D(100.0f, 50.0f));
		WidgetComp->SetRelativeLocation(FVector(2.0f, 0.0f, 0.0f));
		//(Pitch=90.000000,Yaw=0.000000,Roll=0.000000)
		WidgetComp->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	}
}

void ABSU_Memo::SetMemoText(FString Text)
{
	if (WidgetComp)
	{
		UBSU_MemoWidget* Widget = Cast<UBSU_MemoWidget>(WidgetComp->GetUserWidgetObject());
		if (Widget)
		{
			Widget->SetMemo(FText::FromString(Text));
		}
	}
}
