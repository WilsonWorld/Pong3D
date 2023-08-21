// Paddle class for Pong 3D, created by Aaron Wilson, Wilson World Games. May 14th, 2023.
// Paddle class is responsible for managing shared properties between the player and ai paddles.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PongPaddle.generated.h"


UCLASS()
class PONG3D_API APongPaddle : public APawn
{
	GENERATED_BODY()

public:
	APongPaddle();

	UFUNCTION(BlueprintCallable, Category = "MovementVert")
		void VerticalMove(float AxisValue);

	UFUNCTION(BlueprintCallable, Category = "MovementHoriz")
		void HorizontalMove(float AxisValue);

	UFUNCTION()
		void CheckMoveBoundaries();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UStaticMeshComponent* paddleMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<UUserWidget> ReplayWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float paddleSpeed = 10;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float paddleSpeedMin = 25.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float paddleSpeedMax = 50.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int paddleScore = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int scoreLimit = 0;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OpenReplayMenu();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FTimerHandle OpenMenuTimerHandle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class APongGameState* PongGameState;

	UPROPERTY()
		class UReplayMenuWidget* rmWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bIsPlayerPaddle;

	float CurrentMovementVert;
	float CurrentMovementHoriz;
	bool bTimerActive = false;

};
