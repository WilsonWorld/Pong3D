// Pong Ball class for Pong 3D, created by Aaron Wilson, Wilson World Games. May 15th, 2023.
// Pong Ball class is responsible for 3D movement, boucing off game objects, and managing the speed of the ball throughout the game.

#include "PongBall.h"
#include "Components/AudioComponent.h"


APongBall::APongBall()
{
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

	// Lock the mesh from rotating
	pBallMesh->GetBodyInstance()->bLockXRotation = true;
	pBallMesh->GetBodyInstance()->bLockYRotation = true;
	pBallMesh->GetBodyInstance()->bLockZRotation = true;

	// Create and setup the audio component of the ball
	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("Sound Emitter"));
	AudioComp->bAutoActivate = false;
	AudioComp->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	AudioComp->SetupAttachment(RootComponent);
}

void APongBall::BeginPlay()
{
	Super::BeginPlay();
	StartFaceOff();
	AudioComp->SetSound(BounceSound);
}

void APongBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector velocity = pBallMesh->GetComponentVelocity();
	LimitBallSpeed(velocity);
}

// Check if the ball has hit a paddle, and if so, add a burst of speed to it.
void APongBall::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL)) {
		if (!AudioComp->IsPlaying())
			AudioComp->Play();

		if (OtherActor->ActorHasTag("Paddle")) {
			FVector velocity = pBallMesh->GetComponentVelocity();
			velocity = FVector(velocity.X, velocity.Y, velocity.Z) * 0.25f;
			pBallMesh->AddImpulse(velocity, NAME_None, true);
		}
	}
}

// Reset the Pong Ball and add force to begin gameplay
void APongBall::StartFaceOff()
{
	SetAtStartLocation();
	FVector spawnDirection = GenerateRandDirection();
	pBallMesh->AddImpulse(spawnDirection * pBallSpeed, NAME_None, true);
}

// Reset the Pong Ball to middle of game area
void APongBall::SetAtStartLocation()
{
	FVector startLocation = FVector(0.0f, 0.0f, 1350.0f);
	SetActorLocation(startLocation);
}

// Return a vector with a random direction within a -1 to 1 range
FVector APongBall::GenerateRandDirection()
{
	float spawnDirectionX = FMath::RandRange(-1.0f, 1.0f);
	float spawnDirectionY = FMath::RandRange(-1.0f, 1.0f);
	float spawnDirectionZ = FMath::RandRange(-1.0f, 1.0f);
	FVector spawnDirection = FVector(spawnDirectionX, spawnDirectionY, spawnDirectionZ);
	return spawnDirection;
}

// Check the movement speed on each axis and set it to the max speed if the ball goes over the max. Increased speed on the X for improved gameplay.
void APongBall::LimitBallSpeed(FVector speed)
{
	if (speed.X <= ballMaxSpeed * 2.0f && speed.Y <= ballMaxSpeed && speed.Z <= ballMaxSpeed)
		return;

	if (speed.X > ballMaxSpeed * 2.0f) {
		speed.X = ballMaxSpeed * 2.0f;
	}
	if (speed.Y > ballMaxSpeed) {
		speed.Y = ballMaxSpeed;
	}
	if (speed.Z > ballMaxSpeed) {
		speed.Z = ballMaxSpeed;
	}
	pBallMesh->GetBodyInstance()->SetLinearVelocity(speed, false, true);
}