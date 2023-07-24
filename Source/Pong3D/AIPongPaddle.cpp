// AI Paddle class for Pong 3D, created by Aaron Wilson, Wilson World Games. June 16th, 2023.
// AI Paddle class is responsible for tracking the game's Pong Ball and moving a Paddle to block the ball from entering AI Goal Area/Trigger.


#include "AIPongPaddle.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "PongBall.h"
#include "ReplayMenuWidget.h"


void AAIPongPaddle::BeginPlay()
{
	Super::BeginPlay();
	GetPongBall();
	TargetPosition = GetActorLocation();
}

void AAIPongPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ManagePaddleSleep(DeltaTime);

	if (bIsAwake == false)
		return;

	SetPaddleTargetPosition();
	MovePaddle(DeltaTime);

	if (paddleScore < scoreLimit)
		return;
	else{
		// Player Loses
		// Display Defeat Text
		// Open EndGameMenu Widget with options to restart or quit
		if (ReplayWidget)
		{
			UReplayMenuWidget* ReplayMenuWidget = CreateWidget<UReplayMenuWidget>(GetWorld()->GetGameInstance(), ReplayWidget);
			ReplayMenuWidget->AddToViewport(0);
		}

		//m_PongBall->Destroy();
		m_PongBall->SetActorLocation(FVector(0.0f, 0.0f, 1050.0f));
	}
}

// Grab the Pong Ball Actor and store it in the Pong Ball member variable
void AAIPongPaddle::GetPongBall()
{
	AActor* ballActor = UGameplayStatics::GetActorOfClass(GetWorld(), APongBall::StaticClass());
	m_PongBall = Cast<APongBall>(ballActor);
}

// Get the Paddle's current location and update it with the Pong Ball's Y & Z position, storing it inside the FVector member varible
void AAIPongPaddle::SetPaddleTargetPosition()
{
	FVector ballPos = m_PongBall->GetActorLocation();
	FVector TargetLocation = GetActorLocation();
	TargetLocation = FVector(TargetLocation.X, ballPos.Y, ballPos.Z);
	TargetPosition = TargetLocation;
}

// Move the Paddle actor to the Target Position
void AAIPongPaddle::MovePaddle(float DeltaTime)
{
	// IN PROGRESS - Move the Paddle towards the target position rather than setting it's position to the target position
	FVector NewPosition = FMath::VInterpConstantTo(GetActorLocation(), TargetPosition, DeltaTime, Difficulty);
	SetActorLocation(NewPosition);

	// BAD CODE - Sets the paddle position directly to where the target position is (causing teleporting after coming awake)
	//SetActorLocation(TargetPosition);
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