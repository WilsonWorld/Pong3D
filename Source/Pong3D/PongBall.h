// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PongBall.generated.h"

UCLASS()
class PONG3D_API APongBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APongBall();

	UFUNCTION()
		void StartFaceOff();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UStaticMeshComponent* pBallMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float pBallSpeed = 1000.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float pBallBounce = 3.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float ballMaxSpeed = 8000.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
