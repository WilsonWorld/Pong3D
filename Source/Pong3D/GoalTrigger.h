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
	AGoalTrigger();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UStaticMeshComponent* GoalMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bIsPlayerGoal;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Score")
		void IncreaseScore();

	UFUNCTION()
		void ChangeColorMat();

	UFUNCTION()
		void ResetColorMat();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class APongGameState* PongGameState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
		UMaterialInterface* OriginalMat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sound")
		class UAudioComponent* GoalAudio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		class USoundBase* GoalSound;

	UPROPERTY(BlueprintReadOnly)
		FTimerHandle ResetTimerHandle;
};
