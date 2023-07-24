// Goal Trigger class for Pong 3D, created by Aaron Wilson, Wilson World Games. July 16th, 2023.
// Goal Trigger class is responsible for reseting the Pong Ball and incrementing opposing player's score.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoalTrigger.generated.h"

UCLASS()
class PONG3D_API AGoalTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoalTrigger();

	UFUNCTION()
		void ResetBall(class APongBall* ball);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UBoxComponent* GoalBox;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bIsPlayerGoal;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
