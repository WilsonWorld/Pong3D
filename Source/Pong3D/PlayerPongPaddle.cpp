// Player Paddle class for Pong 3D, created by Aaron Wilson, Wilson World Games. May 14th, 2023.
// Player Paddle class is responsible for moving the paddle via the player controller. Ensures movement is within game boundaries and score is tracked.

#include "PlayerPongPaddle.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


APlayerPongPaddle::APlayerPongPaddle()
{
	// Spring Arm & Camera Component 
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	springArm->SetupAttachment(RootComponent);

	paddleCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Paddle Camera"));
	paddleCamera->AttachToComponent(springArm, FAttachmentTransformRules::KeepRelativeTransform);

	springArm->bUsePawnControlRotation = true;
	springArm->bEnableCameraLag = true;
	springArm->TargetArmLength = 300.0f;
}

void APlayerPongPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateSpeed(DeltaTime);
	UpdateLocation(CurrentMovementVert, CurrentMovementHoriz);
	CheckMoveBoundaries();
}

// Called to bind movement functionality to input
void APlayerPongPaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("VertMove", this, &APongPaddle::VerticalMove);
	PlayerInputComponent->BindAxis("HorizMove", this, &APongPaddle::HorizontalMove);
}

// Move the Paddle along the Z-axis / Y-axis until it hits the boundaries
void APlayerPongPaddle::UpdateLocation(float vertMove, float horizMove)
{
	FVector NewLocationZ = GetActorLocation();
	if (vertMove != 0)
		NewLocationZ = GetActorLocation() + (GetActorUpVector() * vertMove * paddleSpeed);

	SetActorLocation(NewLocationZ);

	FVector NewLocationY = GetActorLocation();
	if (horizMove != 0)
		NewLocationY = GetActorLocation() + (GetActorRightVector() * horizMove * paddleSpeed);

	SetActorLocation(NewLocationY);
}

void APlayerPongPaddle::UpdateSpeed(float deltaTime)
{
	if (CurrentMovementVert == 0 && CurrentMovementHoriz == 0) {
		if (paddleSpeed <= paddleSpeedMin) {
			paddleSpeed = paddleSpeedMin;
			return;
		}

		paddleSpeed -= 2.5f * deltaTime;
	}
	else {
		if (paddleSpeed >= paddleSpeedMax) {
			paddleSpeed = paddleSpeedMax;
			return;
		}

		paddleSpeed += 2.5f * deltaTime;
	}
}