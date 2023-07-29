// Pong Ball class for Pong 3D, created by Aaron Wilson, Wilson World Games. May 15th, 2023.
// Pong Ball class is responsible for 3D movement, boucing off game objects, and managing the speed of the ball throughout the game.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PongBall.generated.h"


UCLASS()
class PONG3D_API APongBall : public AActor
{
	GENERATED_BODY()
	
public:	
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
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		void SetAtStartLocation();

	UFUNCTION()
		FVector GenerateRandDirection();

	UFUNCTION()
		void LimitBallSpeed(FVector speed);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sound")
		class UAudioComponent* AudioComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		class USoundBase* BounceSound;

};
