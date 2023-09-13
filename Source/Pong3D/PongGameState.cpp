// Pong Game State class for Pong 3D, created by Aaron Wilson, Wilson World Games. July 22th, 2023.
// Pong Game State class is responsible for managing the game objects.

#include "PongGameState.h"
#include "PongController.h"
#include "ReplayMenuWidget.h"
#include "GameFramework/GameUserSettings.h"


// Set the AI paddle and Pong Ball refererences
APongGameState::APongGameState()
{
	PrimaryActorTick.bCanEverTick = true;

	AActor* paddleAiActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAIPongPaddle::StaticClass());
	AIPaddleRef = Cast<AAIPongPaddle>(paddleAiActor);

	AActor* ballActor = UGameplayStatics::GetActorOfClass(GetWorld(), APongBall::StaticClass());
	PongBallRef = Cast<APongBall>(ballActor);
}

// Sets the player paddle reference at the start of the game when the player is generated.
void APongGameState::BeginPlay()
{
	Super::BeginPlay();
	AActor* paddleActor = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerPongPaddle::StaticClass());
	PlayerPaddleRef = Cast<APlayerPongPaddle>(paddleActor);

	APlayerController* playController = GetWorld()->GetFirstPlayerController();
	APongController* pongController = Cast<APongController>(playController);

	if (pongController) {
		pongController->bShowMouseCursor = false;
		pongController->bEnableClickEvents = false;
		pongController->bEnableMouseOverEvents = false;
	}
}

// Increase game timer by each frame
void APongGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GameTime += DeltaTime;
}

void APongGameState::OpenReplayMenu()
{
	if (ReplayWidget) {
		ReplayMenuWidget = CreateWidget<UReplayMenuWidget>(GetWorld()->GetGameInstance(), ReplayWidget);
		ReplayMenuWidget->AddToViewport(0);

		if (PlayerScore > ComputerScore)
			ReplayMenuWidget->DisplayVictoryText();
		else
			ReplayMenuWidget->DisplayDefeatText();
	}
}

// Increment Player's score 
void APongGameState::IncreasePlayerScore()
{
	PlayerScore++;
	PongBallRef->ResetBall();

	if (PlayerScore >= scoreLimit)
		GetWorld()->GetTimerManager().SetTimer(OpenMenuTimerHandle, this, &APongGameState::OpenReplayMenu, 2.0f, false);
}

// Increment Computer's score 
void APongGameState::IncreaseComputerScore()
{
	ComputerScore++;
	PongBallRef->ResetBall();

	if (ComputerScore >= scoreLimit)
		GetWorld()->GetTimerManager().SetTimer(OpenMenuTimerHandle, this, &APongGameState::OpenReplayMenu, 2.0f, false);
}

// Reset both scores to 0
void APongGameState::ResetScores()
{
	PlayerScore = 0;
	ComputerScore = 0;
}