// Replay Menu Widget class for Pong 3D, created by Aaron Wilson, Wilson World Games. August 20th, 2023.

#include "ReplayMenuWidget.h"
#include "PongController.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"


void UReplayMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ReplayButton->OnClicked.AddUniqueDynamic(this, &UReplayMenuWidget::OnReplayButtonClicked);
	QuitButton->OnClicked.AddUniqueDynamic(this, &UReplayMenuWidget::OnQuitButtonClicked);

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

void UReplayMenuWidget::QuitToMainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenuLevel");
}

void UReplayMenuWidget::OnReplayButtonClicked()
{
	EnableMouseEvents(false);
	ResetLevel();
}

void UReplayMenuWidget::OnQuitButtonClicked()
{
	QuitToMainMenu();
}

void UReplayMenuWidget::EnableMouseEvents(bool state)
{
	if (PongControllerRef) {
		PongControllerRef->bShowMouseCursor = state;
		PongControllerRef->bEnableClickEvents = state;
		PongControllerRef->bEnableMouseOverEvents = state;
	}
}

void UReplayMenuWidget::DisplayVictoryText()
{
	VictoryText->SetVisibility(ESlateVisibility::Visible);
}

void UReplayMenuWidget::DisplayDefeatText()
{
	DefeatText->SetVisibility(ESlateVisibility::Visible);
}