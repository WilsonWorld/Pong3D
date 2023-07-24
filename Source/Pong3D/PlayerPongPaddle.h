// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PongPaddle.h"
#include "PlayerPongPaddle.generated.h"

/**
 * 
 */
UCLASS()
class PONG3D_API APlayerPongPaddle : public APongPaddle
{
	GENERATED_BODY()
	
public:
	APlayerPongPaddle();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class USpringArmComponent* springArm;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UCameraComponent* paddleCamera;

	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
