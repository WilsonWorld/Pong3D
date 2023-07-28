// Fill out your copyright notice in the Description page of Project Settings.


#include "PongPaddle.h"

// Sets default values
APongPaddle::APongPaddle() 
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Paddle Root Object, both collision and visual mesh
	paddleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle Root"));
	SetRootComponent(paddleMesh);
	paddleMesh->SetSimulatePhysics(true);
	paddleMesh->SetEnableGravity(false);
	paddleMesh->SetCollisionProfileName("BlockAllDynamic");
	paddleMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	paddleMesh->GetBodyInstance()->bLockXRotation = true;
	paddleMesh->GetBodyInstance()->bLockYRotation = true;
	paddleMesh->GetBodyInstance()->bLockZRotation = true;
	paddleMesh->GetBodyInstance()->bLockXTranslation = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

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