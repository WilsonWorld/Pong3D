// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/UserWidget.h"
#include "PongPaddle.generated.h"

UCLASS()
class PONG3D_API APongPaddle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APongPaddle();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UStaticMeshComponent* paddleMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<UUserWidget> ReplayWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float paddleSpeed = 10;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int paddleScore = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int scoreLimit = 0;

	UFUNCTION(BlueprintCallable, Category = "MovementVert")
		void VerticalMove(float AxisValue);

	UFUNCTION(BlueprintCallable, Category = "MovementHoriz")
		void HorizontalMove(float AxisValue);

	float CurrentMovementVert;
	float CurrentMovementHoriz;

};
