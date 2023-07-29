// Paddle class for Pong 3D, created by Aaron Wilson, Wilson World Games. July 20th, 2023.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ReplayMenuWidget.generated.h"


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
