// Fill out your copyright notice in the Description page of Project Settings.
// 
// 
// #include "MessageWidget.h"
// 
// void UMessageWidget::NativeConstruct()
// {	
// 
// 	Super:NativeConstruct();
// 
// 	FOnTimelineFloat ProgressFunction;
// 	ProgressFunction.BindUFunction(this, FName("HandleProgress"));
// 
// 	// 종료
// 	FOnTimelineEvent FinishedEvent;
// 	FinishedEvent.BindUFunction(this, FName("WidgetMoveEnd"));
// 
// 	WidgetMoveTimeline.AddInterpFloat(MoveCurve, ProgressFunction);
// 	WidgetMoveTimeline.SetTimelineFinishedFunc(FinishedEvent);
// 
// 	WidgetMoveTimeline.SetLooping(false);
// 
// 	UE_LOG(LogTemp, Warning, TEXT("UHD_PlayerWidget::NativeDestruct()"));
// 	for (auto& DialogHnd : DialogHnds)
// 	{
// 		GetWorld()->GetTimerManager().ClearTimer(DialogHnd);
// 	}
// 
// 	DialogHnds.Empty();
// 
// }
// 
// }
// 
// void UMessageWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
// {
// 
// 	Super::NativeTick(MyGeometry,InDeltaTime)
// 
// 
// 
// 
// 
// }
// 
// void UMessageWidget::AddNarrationWidget(UTranscriptWidget* widget)
// {
// 
// 	// Overlay에 자식이 있다면 마지막 자식을 제거한다.
// 	if (NarrationOverlay->GetChildrenCount() > 0)
// 	{
// 		auto* LastWidget = Cast<UTranscriptWidget>(NarrationOverlay->GetChildAt(NarrationOverlay->GetChildrenCount() - 1));
// 		if (LastWidget)
// 		{
// 			LastWidget->AnimNextWidget();
// 		}
// 	}
// 
// 	NarrationOverlay->AddChild(widget);
// 	FTimerHandle DialogHnd;
// 
// 	WidgetMoveTimeline.PlayFromStart();
// 	widget->AnimStartWidget();
// 
// 	UE_LOG(LogTemp, Warning, TEXT("UHD_PlayerWidget::AddNarrationWidget()"));
// 	GetWorld()->GetTimerManager().SetTimer(DialogHnd, [this, &DialogHnd, widget]() {
// 		if (widget)
// 		{
// 			DialogHnds.Remove(DialogHnd);
// 			EnVisibleTextBlock(widget);
// 			widget->AnimHideWidget();
// 		}
// 		}, 15.0f, false);
// 
// 	DialogHnds.Add(DialogHnd);
// 
// 	
// }
// 
// void UMessageWidget::HandleProgress(float Value)
// {
// }
// 
// void UMessageWidget::WidgetMoveEnd()
// {
// }
// 
// void UMessageWidget::ShowDialogForDuration(UTexture2D* Icon, FString Name, FString Description)
// {
// 
// }
// 
// void UMessageWidget::EnVisibleTextBlock(UTranscriptWidget* widget)
// {
// }
