// Goal Trigger class for Pong 3D, created by Aaron Wilson, Wilson World Games. July 16th, 2023.
// Goal Trigger class is responsible for reseting the Pong Ball and incrementing opposing player's score.


#include "GoalTrigger.h"
#include "PongBall.h"
#include "AIPongPaddle.h"
#include "PlayerPongPaddle.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGoalTrigger::AGoalTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GoalBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	SetRootComponent(GoalBox);
	GoalBox->SetSimulatePhysics(true);
	GoalBox->SetEnableGravity(false);
	GoalBox->SetNotifyRigidBodyCollision(true);
	GoalBox->SetCollisionProfileName("OverlapAllDynamic");
	GoalBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GoalBox->OnComponentBeginOverlap.AddDynamic(this, &AGoalTrigger::OnOverlap);

}

// Called when the game starts or when spawned
void AGoalTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGoalTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGoalTrigger::OnOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		if (bIsPlayerGoal == true)
		{
			AActor* pActor = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerPongPaddle::StaticClass());
			APlayerPongPaddle* playerPaddle = Cast<APlayerPongPaddle>(pActor);
			playerPaddle->paddleScore++;

			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue,(TEXT("Player Score: " + FString::FromInt(playerPaddle->paddleScore))));
		}
		else
		{
			AActor* pActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAIPongPaddle::StaticClass());
			AAIPongPaddle* aiPaddle = Cast<AAIPongPaddle>(pActor);
			aiPaddle->paddleScore++;

			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, (TEXT("AI Score: " + FString::FromInt(aiPaddle->paddleScore))));
		}

		APongBall* pBall = Cast<APongBall>(OtherActor);
		if (pBall != NULL)
		{
			ResetBall(pBall);
		}
	}
}

void AGoalTrigger::ResetBall(APongBall* ball)
{
	ball->StartFaceOff();
}