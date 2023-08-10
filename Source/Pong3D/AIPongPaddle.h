// AI Paddle class for Pong 3D, created by Aaron Wilson, Wilson World Games. June 16th, 2023.
// AI Paddle class is responsible for tracking the game's Pong Ball and moving a Paddle to block the ball from entering AI Goal Area/Trigger.

#pragma once

#include "CoreMinimal.h"
#include "PongPaddle.h"
#include "AIPongPaddle.generated.h"


UCLASS()
class PONG3D_API AAIPongPaddle : public APongPaddle
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "MovementAI")
		class APongBall* GetPongBall();

	UFUNCTION(BlueprintCallable, Category = "MovementAI")
		void SetPaddleTargetPosition();

	UFUNCTION(BlueprintCallable, Category = "MovementAI")
		void MovePaddle(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "MovementAI")
		void ManagePaddleSleep(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "MovementAI")
		void IncreaseDifficulty();

	UFUNCTION(BlueprintCallable, Category = "MovementAI")
		void ResetDifficulty();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float AwakeDuration = 5.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float SleepDuration = 0.75f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float StartingDifficulty = 1000.0f;

private:
	UPROPERTY()
		float Difficulty;

	FVector TargetPosition;
	float AwakeTime = 0.0f;
	float SleepTime = 0.0f;
	bool bIsAwake = true;
};
