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

	UFUNCTION()
		void ResetBall();

	UFUNCTION()
		void PlayGoalFX();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UStaticMeshComponent* pBallMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float pBallSpeed = 2000.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float ballMaxSpeed = 6000.0f;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		void SetAtStartLocation();

	UFUNCTION()
		void SetStartVelocity();

	UFUNCTION()
		FVector GenerateRandDirection();

	UFUNCTION()
		void MoveTowardsPlayer();

	UFUNCTION()
		void LimitBallSpeed(FVector speed);

	UFUNCTION()
		void StopMovement();

	UFUNCTION()
		void AddSpeed();

	UFUNCTION()
		void ChangeSize();

	UFUNCTION()
		void ResetSize();

	UFUNCTION()
		void ChangeColor();

	UFUNCTION()
		void PlayBounceFX(FVector location);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
		UMaterialInterface* OriginalMat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
		UMaterialInstance* MatInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sound")
		class UAudioComponent* AudioComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		class USoundBase* BounceSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
		class UNiagaraSystem* GoalExplosionPFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
		class UNiagaraSystem* BouncePFX;

	UPROPERTY(BlueprintReadOnly)
		FTimerHandle ResetTimerHandle;

};
