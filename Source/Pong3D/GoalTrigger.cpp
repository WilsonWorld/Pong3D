// Goal Trigger class for Pong 3D, created by Aaron Wilson, Wilson World Games. July 16th, 2023.
// Goal Trigger class is responsible for reseting the Pong Ball and incrementing opposing player's score.

#include "GoalTrigger.h"
#include "PongGameState.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"


AGoalTrigger::AGoalTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create and set up the box trigger to detect overlaps
	GoalBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	SetRootComponent(GoalBox);
	GoalBox->SetSimulatePhysics(true);
	GoalBox->SetEnableGravity(false);
	GoalBox->SetNotifyRigidBodyCollision(true);
	GoalBox->SetCollisionProfileName("OverlapAllDynamic");
	GoalBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GoalBox->OnComponentBeginOverlap.AddDynamic(this, &AGoalTrigger::OnOverlap);

	// Audtio Component
	GoalAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("Sound Emitter"));
	GoalAudio->bAutoActivate = false;
	GoalAudio->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	GoalAudio->SetupAttachment(RootComponent);
}

void AGoalTrigger::BeginPlay()
{
	Super::BeginPlay();
	PongGameState = Cast<APongGameState>(GetWorld()->GetGameState());
	GoalAudio->SetSound(GoalSound);
}

//Check for objects overlaping this trigger, only ball can hit this. Check if it is set as the player or ai and update the score accordingly
void AGoalTrigger::OnOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL)) {
		if (GoalAudio)
			GoalAudio->Play();

		if (bIsPlayerGoal == true)
			PongGameState->PlayerPaddleRef->paddleScore++;
		else
			PongGameState->AIPaddleRef->paddleScore++;

		APongBall* pBall = Cast<APongBall>(OtherActor);
		if (pBall != NULL)
			ResetBall(pBall);
	}
}

// Resets the ball 
void AGoalTrigger::ResetBall(APongBall* ball)
{
	ball->ResetBall();
}