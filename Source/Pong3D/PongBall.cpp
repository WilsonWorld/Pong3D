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

	// Create and setup the audio component of the ball
	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("Sound Emitter"));
	AudioComp->bAutoActivate = false;
	AudioComp->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	AudioComp->SetupAttachment(RootComponent);

	OriginalMat = pBallMesh->GetMaterial(0);
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

// Check if the ball has hit anything to play bounce sound on the audio component; if colliding with paddle, change color and size while adding a burst of speed
void APongBall::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL)) {
		if (AudioComp)
			AudioComp->Play();

		if (OtherActor->ActorHasTag("Paddle")) {
			AddSpeed();
			ChangeColor();
			ChangeSize();
		}
	}
}

// Public method for resetting the Pong Ball back to the start after the timer elasped
void APongBall::ResetBall()
{
	StopMovement();
	SetAtStartLocation();
	ResetSize();
	pBallMesh->SetVisibility(false);
	GetWorld()->GetTimerManager().SetTimer(ResetTimerHandle, this, &APongBall::StartFaceOff, 3.0f, false);
}

// Reset the Reset Timer Handle and move the Pong Ball to the start with a random starting velocity
void APongBall::StartFaceOff()
{
	pBallMesh->SetVisibility(true);
	GetWorld()->GetTimerManager().ClearTimer(ResetTimerHandle);
	SetAtStartLocation();
	SetStartVelocity();
	MoveTowardsPlayer();
}

// Reset the Pong Ball to middle of game area
void APongBall::SetAtStartLocation()
{
	FVector startLocation = FVector(0.0f, 0.0f, 3850.0f);
	SetActorLocation(startLocation);
}

// Set the starting velocity based on a random 3D direction and starting speed
void APongBall::SetStartVelocity()
{
	FVector spawnDirection = GenerateRandDirection();
	pBallMesh->AddImpulse(spawnDirection * pBallSpeed, NAME_None, true);
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

// Randomly adds a full move value towards either player
void APongBall::MoveTowardsPlayer()
{
	int RandPlayerStart = FMath::RandRange(0, 1);
	if (RandPlayerStart == 0)
		pBallMesh->AddImpulse(pBallMesh->GetRightVector() * pBallSpeed, NAME_None, true);
	else
		pBallMesh->AddImpulse(-pBallMesh->GetRightVector() * pBallSpeed, NAME_None, true);
}

// Check the movement speed on each axis and set it to the max speed if the ball goes over the max. Increased speed on the X for improved gameplay.
void APongBall::LimitBallSpeed(FVector speed)
{
	if (speed.X <= ballMaxSpeed * 2.0f && speed.Y <= ballMaxSpeed && speed.Z <= ballMaxSpeed)
		return;

	if (speed.X > ballMaxSpeed * 2.0f) 
		speed.X = ballMaxSpeed * 2.0f;

	if (speed.Y > ballMaxSpeed) 
		speed.Y = ballMaxSpeed;

	if (speed.Z > ballMaxSpeed) 
		speed.Z = ballMaxSpeed;

	pBallMesh->GetBodyInstance()->SetLinearVelocity(speed, false, true);
}

// Forcibly stop all movement on the Pong Ball
void APongBall::StopMovement()
{
	FVector zeroVel = FVector::ZeroVector;
	pBallMesh->GetBodyInstance()->SetLinearVelocity(zeroVel, false, true);
}

// Add a 20% burst of speed
void APongBall::AddSpeed()
{
	FVector velocity = pBallMesh->GetComponentVelocity();
	velocity = FVector(velocity.X, velocity.Y, velocity.Z) * 0.20f;
	pBallMesh->AddImpulse(velocity, NAME_None, true);
}

// Decrease the size of the ball by 5%
void APongBall::ChangeSize()
{
	FVector newSize = pBallMesh->GetRelativeScale3D() * 0.95f;
	pBallMesh->SetWorldScale3D(newSize);
}

// Reset Pong Ball to orginal 100% scale size
void APongBall::ResetSize()
{
	FVector originalSize = FVector::One();
	pBallMesh->SetWorldScale3D(originalSize);
}

// Change the color of the ball to random new one
void APongBall::ChangeColor()
{
	UMaterialInstanceDynamic* newMat = UMaterialInstanceDynamic::Create(OriginalMat, this);
	float randR = FMath::RandRange(0.0f, 1.0f);
	float randG = FMath::RandRange(0.0f, 1.0f);
	float randB = FMath::RandRange(0.0f, 1.0f);
	FVector4 randColor = FVector4(randR, randG, randB, 1.0f);
	newMat->SetVectorParameterValue("MatColor", randColor);
	pBallMesh->SetMaterial(0, newMat);
}