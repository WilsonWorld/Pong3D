// Goal Trigger class for Pong 3D, created by Aaron Wilson, Wilson World Games. July 16th, 2023.
// Goal Trigger class is responsible for reseting the Pong Ball and incrementing opposing player's score.

#include "GoalTrigger.h"
#include "PongGameState.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"


AGoalTrigger::AGoalTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

	// Mesh Component
	GoalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Trigger Box"));
	SetRootComponent(GoalMesh);
	GoalMesh->SetSimulatePhysics(false);
	GoalMesh->SetEnableGravity(false);
	GoalMesh->SetNotifyRigidBodyCollision(true);
	GoalMesh->SetCollisionProfileName("OverlapAllDynamic");
	GoalMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GoalMesh->OnComponentBeginOverlap.AddDynamic(this, &AGoalTrigger::OnOverlap);

	// Audtio Component
	GoalAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("Sound Emitter"));
	GoalAudio->SetupAttachment(RootComponent);
	GoalAudio->bAutoActivate = false;
	GoalAudio->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
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
		PongGameState->PongBallRef->PlayGoalFX();
		PongGameState->PongBallRef->ResetBall();
		
		if (bIsPlayerGoal)
			return;
		
		ChangeColorMat();
	}
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

// Create a copy of the original material, changing it's color to red  to use for 0.5 seconds before resetting to original mat.
void AGoalTrigger::ChangeColorMat()
{
	UMaterialInstanceDynamic* newMat = UMaterialInstanceDynamic::Create(OriginalMat, this);
	FVector scoreColor = FVector(255.0f, 0.0f, 0.0f);
	newMat->SetVectorParameterValue("MatColor", scoreColor);
	GoalMesh->SetMaterial(0, newMat);
	GetWorld()->GetTimerManager().SetTimer(ResetTimerHandle, this, &AGoalTrigger::ResetColorMat, 0.5f, false);
}

// Changes the mesh back to the original material and resets the Reset Timer Handle
void AGoalTrigger::ResetColorMat()
{
	GoalMesh->SetMaterial(0, OriginalMat);
	GetWorld()->GetTimerManager().ClearTimer(ResetTimerHandle);
}