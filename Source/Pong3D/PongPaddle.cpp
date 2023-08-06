// Paddle class for Pong 3D, created by Aaron Wilson, Wilson World Games. May 14th, 2023.
// Paddle class is responsible for managing shared properties between the player and ai paddles.

#include "PongPaddle.h"
#include "PongGameState.h"
#include "ReplayMenuWidget.h"


APongPaddle::APongPaddle() 
{
	PrimaryActorTick.bCanEverTick = true;

	// Paddle Root Object, both collision and visual mesh
	paddleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle Root"));
	SetRootComponent(paddleMesh);
	paddleMesh->SetSimulatePhysics(true);
	paddleMesh->SetEnableGravity(false);
	paddleMesh->SetCollisionProfileName("BlockAllDynamic");
	paddleMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	// Prevent physics body from rotating or moving when hit by the Pong Ball
	paddleMesh->GetBodyInstance()->bLockXRotation = true;
	paddleMesh->GetBodyInstance()->bLockYRotation = true;
	paddleMesh->GetBodyInstance()->bLockZRotation = true;
	paddleMesh->GetBodyInstance()->bLockXTranslation = true;

	// Don't rotate the paddle when the mouse/camera control is moved
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void APongPaddle::BeginPlay()
{
	Super::BeginPlay();
	PongGameState = Cast<APongGameState>(GetWorld()->GetGameState());
}

void APongPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (paddleScore < scoreLimit)
		return;
	else {
		if (bTimerActive)
			return;

		bTimerActive = true;
		GetWorld()->GetTimerManager().SetTimer(OpenMenuTimerHandle, this, &APongPaddle::OpenReplayMenu, 2.0f, false);
	}
}

// Move the paddle up and down
void APongPaddle::VerticalMove(float AxisValue)
{
	CurrentMovementVert = AxisValue;
}

// Move the paddle left and right
void APongPaddle::HorizontalMove(float AxisValue)
{
	CurrentMovementHoriz = AxisValue;
}

// Stop the paddle from moving into/over game area boundaries
void APongPaddle::CheckMoveBoundaries()
{
	// Move the Paddle along the Z-axis until they hit the boundaries
	FVector NewLocationZ = GetActorLocation();
	if (NewLocationZ.Z <= 600.0f)
		NewLocationZ.Z = 600.0f;
	if (NewLocationZ.Z >= 2100.0f)
		NewLocationZ.Z = 2100.0f;

	SetActorLocation(NewLocationZ);

	// Move the Paddle along the Y-axis until they hit the boundaries
	FVector NewLocationY = GetActorLocation();
	if (NewLocationY.Y >= 1900.0f)
		NewLocationY.Y = 1900.0f;
	if (NewLocationY.Y <= -1900.0f)
		NewLocationY.Y = -1900.0f;

	SetActorLocation(NewLocationY);
}

void APongPaddle::OpenReplayMenu()
{
	if (ReplayWidget) {
		rmWidget = CreateWidget<UReplayMenuWidget>(GetWorld()->GetGameInstance(), ReplayWidget);
		rmWidget->AddToViewport(0);

		if (bIsPlayerPaddle)
			rmWidget->DisplayVictoryText();
		else
			rmWidget->DisplayDefeatText();
	}
}