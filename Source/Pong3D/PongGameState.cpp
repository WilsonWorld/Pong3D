// Pong Game State class for Pong 3D, created by Aaron Wilson, Wilson World Games. July 22th, 2023.
// Pong Game State class is responsible for managing the game state and resetting the game.


#include "PongGameState.h"
#include "PlayerPongPaddle.h"
#include "AIPongPaddle.h"
#include "PongBall.h"
#include "Kismet/GameplayStatics.h"

APongGameState::APongGameState()
{
	AActor* paddleAiActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAIPongPaddle::StaticClass());
	AIPaddle = Cast<AAIPongPaddle>(paddleAiActor);

	AActor* ballActor = UGameplayStatics::GetActorOfClass(GetWorld(), APongBall::StaticClass());
	PongBall = Cast<APongBall>(ballActor);
}

void APongGameState::BeginPlay()
{
	Super::BeginPlay();

	AActor* paddleActor = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerPongPaddle::StaticClass());
	PlayerPaddle = Cast<APlayerPongPaddle>(paddleActor);
}

void APongGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (PlayerPaddle != NULL)
		PlayerScore = PlayerPaddle->paddleScore;

	//if (AIPaddle != NULL)
		AIScore = AIPaddle->paddleScore;

	if (PlayerScore >= ScoreLimit)
	{
		// Player Wins
		// Display Victory Text
		// Open EndGameMenu Widget with options to restart or quit
		PongBall->Destroy();
	}

	if (AIScore >= ScoreLimit)
	{
		// Player Loses
		// Display Defeat Text
		// Open EndGameMenu Widget with options to restart or quit
		PongBall->Destroy();
	}
}