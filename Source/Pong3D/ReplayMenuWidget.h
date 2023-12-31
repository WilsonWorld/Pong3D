// Replay Menu Widget class for Pong 3D, created by Aaron Wilson, Wilson World Games. August 20th, 2023.

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

	UPROPERTY(meta = (BindWidget))
		class UButton* MainMenuButton;

		UPROPERTY(meta = (BindWidget))
		class UButton* QuitButton;

	UPROPERTY()
		class UTextBlock* VictoryText;

	UPROPERTY()
		class UTextBlock* DefeatText;

	UFUNCTION()
		void EnableMouseEvents(bool state);

	UFUNCTION()
		void DisplayVictoryText();

	UFUNCTION()
		void DisplayDefeatText();

protected:
	void NativeConstruct() override;

	void ResetLevel();

	void QuitToMainMenu();

	void QuitGame();

	UFUNCTION()
		void OnReplayButtonClicked();

	UFUNCTION()
		void OnMainMenuButtonClicked();

	UFUNCTION()
		void OnQuitButtonClicked();

	UPROPERTY()
		class APongController* PongControllerRef;
	
};
