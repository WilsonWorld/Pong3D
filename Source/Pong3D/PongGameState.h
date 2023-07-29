// Pong Game State class for Pong 3D, created by Aaron Wilson, Wilson World Games. July 22th, 2023.
// Pong Game State class is responsible for managing the game objects.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PlayerPongPaddle.h"
#include "AIPongPaddle.h"
#include "PongBall.h"
#include "Kismet/GameplayStatics.h"
#include "PongGameState.generated.h"


UCLASS()
class PONG3D_API APongGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	APongGameState();

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		APlayerPongPaddle* PlayerPaddleRef;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		AAIPongPaddle* AIPaddleRef;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		APongBall* PongBallRef;
	
};
