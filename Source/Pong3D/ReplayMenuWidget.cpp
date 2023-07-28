// Fill out your copyright notice in the Description page of Project Settings.


#include "ReplayMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "PongController.h"

void UReplayMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ReplayButton->OnClicked.AddUniqueDynamic(this, &UReplayMenuWidget::OnReplayButtonClicked);

	APlayerController* playController = GetWorld()->GetFirstPlayerController();
	APongController* pongController = Cast<APongController>(playController);

	if (pongController)
		PongControllerRef = pongController;

	EnableMouseEvents(true);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void UReplayMenuWidget::ResetLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), GetWorld()->GetLevel(0)->GetFName());
}

void UReplayMenuWidget::OnReplayButtonClicked()
{
	EnableMouseEvents(false);
	ResetLevel();
}

void UReplayMenuWidget::EnableMouseEvents(bool state)
{
	if (PongControllerRef) {
		PongControllerRef->bShowMouseCursor = state;
		PongControllerRef->bEnableClickEvents = state;
		PongControllerRef->bEnableMouseOverEvents = state;
	}
}