// Pong Game State class for Pong 3D, created by Aaron Wilson, Wilson World Games. July 22th, 2023.
// Pong Game State class is responsible for managing the game objects.

#include "PongGameState.h"


APongGameState::APongGameState()
{
	AActor* paddleAiActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAIPongPaddle::StaticClass());
	AIPaddleRef = Cast<AAIPongPaddle>(paddleAiActor);

	AActor* ballActor = UGameplayStatics::GetActorOfClass(GetWorld(), APongBall::StaticClass());
	PongBallRef = Cast<APongBall>(ballActor);
}

void APongGameState::BeginPlay()
{
	Super::BeginPlay();
	AActor* paddleActor = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerPongPaddle::StaticClass());
	PlayerPaddleRef = Cast<APlayerPongPaddle>(paddleActor);
}