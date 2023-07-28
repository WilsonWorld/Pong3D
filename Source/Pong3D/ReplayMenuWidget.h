// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ReplayMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class PONG3D_API UReplayMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
		class UButton* ReplayButton;

	UFUNCTION()
		void EnableMouseEvents(bool state);

protected:
	void NativeConstruct() override;

	void ResetLevel();

	UFUNCTION()
		void OnReplayButtonClicked();

	UPROPERTY()
		class APongController* PongControllerRef;
	
};
