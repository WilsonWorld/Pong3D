// Goal Trigger class for Pong 3D, created by Aaron Wilson, Wilson World Games. July 16th, 2023.
// Goal Trigger class is responsible for reseting the Pong Ball and incrementing opposing player's score.

#include "GoalTrigger.h"
#include "PongGameState.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"


AGoalTrigger::AGoalTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create the Mesh
	GoalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Trigger Box"));
	SetRootComponent(GoalMesh);
	GoalMesh->SetSimulatePhysics(true);
	GoalMesh->SetEnableGravity(false);
	GoalMesh->SetNotifyRigidBodyCollision(true);
	GoalMesh->SetCollisionProfileName("OverlapAllDynamic");
	GoalMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GoalMesh->OnComponentBeginOverlap.AddDynamic(this, &AGoalTrigger::OnOverlap);

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
	OriginalMat = GoalMesh->GetMaterial(0);
	GoalAudio->SetSound(GoalSound);
}

//Check for objects overlaping this trigger, only ball can hit this. Check if it is set as the player or ai and update the score accordingly
void AGoalTrigger::OnOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL)) {
		if (GoalAudio)
			GoalAudio->Play();

		IncreaseScore();
		PongGameState->PongBallRef->ResetBall();
		
		if (bIsPlayerGoal)
			return;

		UMaterialInstanceDynamic* newMat = UMaterialInstanceDynamic::Create(OriginalMat, this);
		FHitResult hit = SweepResult;
		newMat->SetVectorParameterValue("Pos", hit.ImpactPoint); /* IMPACT RETURNING 0,0,0 - NEEDS FIX*/
		newMat->SetScalarParameterValue("Radius", 50.0f);
		GoalMesh->SetMaterial(0, newMat);
	}
}

// Resets the ball 
void AGoalTrigger::ResetBall(APongBall* ball)
{
	ball->ResetBall();
}

// Check which trigger went off through the bool; increase the score of opposing player and increase ai difficulty if scored on the non-player goal
void AGoalTrigger::IncreaseScore()
{
	if (bIsPlayerGoal == false) {
		PongGameState->PlayerPaddleRef->paddleScore++;
		PongGameState->AIPaddleRef->IncreaseDifficulty();
	}
	else
		PongGameState->AIPaddleRef->paddleScore++;
}