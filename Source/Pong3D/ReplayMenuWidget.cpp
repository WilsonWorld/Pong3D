// Fill out your copyright notice in the Description page of Project Settings.


#include "ReplayMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UReplayMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ReplayButton->OnClicked.AddUniqueDynamic(this, &UReplayMenuWidget::OnReplayButtonClicked);
}

void UReplayMenuWidget::ResetLevel()
{
		UGameplayStatics::OpenLevel(GetWorld(), GetWorld()->GetLevel(0)->GetFName());
}

void UReplayMenuWidget::OnReplayButtonClicked()
{
	ResetLevel();
}