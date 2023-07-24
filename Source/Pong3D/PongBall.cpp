// Fill out your copyright notice in the Description page of Project Settings.


#include "PongBall.h"
#include "PongPaddle.h"


APongBall::APongBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Ball Root Object, both collision and visual mesh
	pBallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball Root"));
	SetRootComponent(pBallMesh);
	pBallMesh->SetSimulatePhysics(true);
	pBallMesh->SetEnableGravity(false);
	pBallMesh->SetNotifyRigidBodyCollision(true);
	pBallMesh->SetCollisionProfileName("BlockAllDynamic");
	pBallMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	pBallMesh->OnComponentHit.AddDynamic(this, &APongBall::OnHit);

	pBallMesh->GetBodyInstance()->bLockXRotation = true;
	pBallMesh->GetBodyInstance()->bLockYRotation = true;
	pBallMesh->GetBodyInstance()->bLockZRotation = true;
}

void APongBall::BeginPlay()
{
	Super::BeginPlay();
	
	float spawnDirectionX = FMath::RandRange(-1.0f, 1.0f);
	float spawnDirectionY = FMath::RandRange(-1.0f, 1.0f);
	float spawnDirectionZ = FMath::RandRange(-1.0f, 1.0f);
	FVector spawnDirection = FVector(spawnDirectionX, spawnDirectionY, spawnDirectionZ);
	pBallMesh->AddImpulse(spawnDirection * pBallSpeed, NAME_None, true);
}

void APongBall::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		if (OtherActor->ActorHasTag("Paddle")) {
			FVector velocity = pBallMesh->GetComponentVelocity();
			velocity = FVector(velocity.X, velocity.Y, velocity.Z) * 0.25f;
			//pBallMesh->AddForce(velocity * pBallBounce, NAME_None, true);
			pBallMesh->AddImpulse(velocity, NAME_None, true);
		}
	}
}

void APongBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector velocity = pBallMesh->GetComponentVelocity();
	float speedX = velocity.X;
	float speedY = velocity.Y;
	float speedZ = velocity.Z;

	if (speedX > ballMaxSpeed * 2.0f)
	{
		velocity.X = ballMaxSpeed * 2.0f;
		pBallMesh->GetBodyInstance()->SetLinearVelocity(velocity, false, true);
	}
	if (speedY > ballMaxSpeed)
	{
		velocity.Y = ballMaxSpeed;
		pBallMesh->GetBodyInstance()->SetLinearVelocity(velocity, false, true);
	}
	if (speedZ > ballMaxSpeed)
	{
		velocity.Z = ballMaxSpeed;
		pBallMesh->GetBodyInstance()->SetLinearVelocity(velocity, false, true);
	}
}

// Reset the Pong Ball to middle of game area and add force in a random direction
void APongBall::StartFaceOff()
{
	FVector startLocation = FVector(0.0f, 0.0f, 1050.0f);
	SetActorLocation(startLocation);

	float spawnDirectionX = FMath::RandRange(-1.0f, 1.0f);
	float spawnDirectionY = FMath::RandRange(-1.0f, 1.0f);
	float spawnDirectionZ = FMath::RandRange(-1.0f, 1.0f);
	FVector spawnDirection = FVector(spawnDirectionX, spawnDirectionY, spawnDirectionZ);
	pBallMesh->AddImpulse(spawnDirection * pBallSpeed, NAME_None, true);
}