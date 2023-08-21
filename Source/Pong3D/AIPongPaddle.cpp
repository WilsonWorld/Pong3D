// AI Paddle class for Pong 3D, created by Aaron Wilson, Wilson World Games. June 16th, 2023.
// AI Paddle class is responsible for tracking the game's Pong Ball and moving a Paddle to block the ball from entering AI Goal Area/Trigger.

#include "AIPongPaddle.h"
#include "PongGameState.h"
#include "Math/UnrealMathUtility.h"


void AAIPongPaddle::BeginPlay()
{
	Super::BeginPlay();
	TargetPosition = GetActorLocation();
	ResetDifficulty();
	GetPongBall();
}

void AAIPongPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ManagePaddleSleep(DeltaTime);

	if (bIsAwake == false)
		return;

	SetPaddleTargetPosition();
	MovePaddle(DeltaTime);
}

// Grab the Pong Ball Actor and store it in the Pong Ball member variable
APongBall* AAIPongPaddle::GetPongBall()
{
	return PongGameState->PongBallRef;
}

// Get the Paddle's current location and update it with the Pong Ball's Y & Z position, storing it inside the FVector member varible
void AAIPongPaddle::SetPaddleTargetPosition()
{
	FVector ballPos = GetPongBall()->GetActorLocation();
	FVector TargetLocation = GetActorLocation();
	TargetLocation = FVector(TargetLocation.X, ballPos.Y, ballPos.Z);
	TargetPosition = TargetLocation;
}

// Move the Paddle actor to the Target Position
void AAIPongPaddle::MovePaddle(float DeltaTime)
{
	FVector NewPosition = FMath::VInterpConstantTo(GetActorLocation(), TargetPosition, DeltaTime, Difficulty * paddleSpeedMax);
	SetActorLocation(NewPosition);
	CheckMoveBoundaries();
}

// Manage Paddle's sleep state based off the duration of time that passes and how long should be spent in each state
void AAIPongPaddle::ManagePaddleSleep(float DeltaTime)
{
	if (bIsAwake) {
		AwakeTime += DeltaTime;

		if (AwakeTime >= AwakeDuration) {
			bIsAwake = false;
			AwakeTime = 0.0f;
		}
	}
	else {
		SleepTime += DeltaTime;

		if (SleepTime >= SleepDuration) {
			bIsAwake = true;
			SleepTime = 0.0f;
		}
	}
}

// Increase the response difficulty by 20%; increases the speed of which the paddle arrives at it's target position
void AAIPongPaddle::IncreaseDifficulty()
{
	Difficulty *= 1.2f;
}

void AAIPongPaddle::ResetDifficulty()
{
	Difficulty = StartingDifficulty;
}