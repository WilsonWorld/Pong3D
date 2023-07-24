// Pong Game State class for Pong 3D, created by Aaron Wilson, Wilson World Games. July 22th, 2023.
// Pong Game State class is responsible for managing the game state and resetting the game.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PongGameState.generated.h"


UCLASS()
class PONG3D_API APongGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	APongGameState();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class APlayerPongPaddle* PlayerPaddle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class AAIPongPaddle* AIPaddle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class APongBall* PongBall;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int ScoreLimit = 5;

private:
	int PlayerScore = 0;
	int AIScore = 0;
	
};
