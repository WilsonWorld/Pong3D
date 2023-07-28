// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPongPaddle.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "PongBall.h"
#include "ReplayMenuWidget.h"

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

	// Move the Paddle along the Z-axis until they hit the boundaries
	FVector NewLocationZ = GetActorLocation();
	if (CurrentMovementVert != 0)
		NewLocationZ = GetActorLocation() + (GetActorUpVector() * CurrentMovementVert * paddleSpeed);

	SetActorLocation(NewLocationZ);

	// Move the Paddle along the Y-axis until they hit the boundaries
	FVector NewLocationY = GetActorLocation();
	if (CurrentMovementHoriz != 0)
		NewLocationY = GetActorLocation() + (GetActorRightVector() * CurrentMovementHoriz * paddleSpeed);

	SetActorLocation(NewLocationY);

	CheckMoveBoundaries();

	if (paddleScore < scoreLimit)
		return;
	else {
		if (ReplayWidget) {
			UReplayMenuWidget* ReplayMenuWidget = CreateWidget<UReplayMenuWidget>(GetWorld()->GetGameInstance(), ReplayWidget);
			ReplayMenuWidget->AddToViewport(0);
		}
	}
}

// Called to bind functionality to input
void APlayerPongPaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("VertMove", this, &APongPaddle::VerticalMove);
	PlayerInputComponent->BindAxis("HorizMove", this, &APongPaddle::HorizontalMove);
}