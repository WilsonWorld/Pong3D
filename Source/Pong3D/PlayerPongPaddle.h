// Player Paddle class for Pong 3D, created by Aaron Wilson, Wilson World Games. May 14th, 2023.
// Player Paddle class is responsible for moving the paddle via the player controller. Ensures movement is within game boundaries and score is tracked.

#pragma once

#include "CoreMinimal.h"
#include "PongPaddle.h"
#include "PlayerPongPaddle.generated.h"


UCLASS()
class PONG3D_API APlayerPongPaddle : public APongPaddle
{
	GENERATED_BODY()
	
public:
	APlayerPongPaddle();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UFUNCTION()
		void UpdateLocation(float vertMove, float horizMove);

	UFUNCTION()
		void UpdateSpeed(float deltaTime);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class USpringArmComponent* springArm;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UCameraComponent* paddleCamera;
};
