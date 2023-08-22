// Pong 3D HUD class for Pong 3D, created by Aaron Wilson, Wilson World Games. July 16th, 2023.
// Pong 3D HUD class is responsible for displaying the player's score and AI's score.

#include "Pong3DHUD.h"
#include "PongGameState.h"
#include "Engine.h"
#include "Components/Image.h"


APong3DHUD::APong3DHUD()
{
}

void APong3DHUD::BeginPlay()
{
	Super::BeginPlay();
	PongGameStateRef = Cast<APongGameState>(GetWorld()->GetGameState());
	CurrentViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
}

void APong3DHUD::DrawHUD()
{
	Super::DrawHUD();
	DrawTextBackground();
	DrawHudText();
	DrawGameClock();
}

void APong3DHUD::DrawTextBackground()
{
	DrawRect(FLinearColor::Black, CurrentViewportSize.X * 0.20f - 70.0f, CurrentViewportSize.Y * 0.05f - 2.5f, 140.0f, 30.0f);	// Player Score
	DrawRect(FLinearColor::Black, CurrentViewportSize.X * 0.80f - 85.0f, CurrentViewportSize.Y * 0.05f - 2.5f, 170.0f, 30.0f);	// Computer Score
	DrawRect(FLinearColor::Black, CurrentViewportSize.X * 0.50f - 55.0f, CurrentViewportSize.Y * 0.05f - 2.5f, 107.5f, 30.0f);	// Clock
}

void APong3DHUD::DrawHudText()
{
	FString HUDStringPlayerScore = FString::Printf(TEXT("Player Score: %d"), PongGameStateRef->PlayerScore);
	FString HUDStringComputerScore = FString::Printf(TEXT("Opponent Score: %d"), PongGameStateRef->ComputerScore);

	DrawText(HUDStringPlayerScore, FColor::White, CurrentViewportSize.X * 0.20f - 65.0f, CurrentViewportSize.Y * 0.05f, HUDFont);
	DrawText(HUDStringComputerScore, FColor::White, CurrentViewportSize.X * 0.80f - 80.0f, CurrentViewportSize.Y * 0.05f, HUDFont);
}

void APong3DHUD::DrawGameClock()
{
	// Seconds to HH : MM : SS Conversion
	float hours = PongGameStateRef->GameTime / 3600.0f;
	int roundedHours = (int)hours;
	float minutes = (hours - roundedHours) * 60.0f;
	int roundedMinutes = (int)minutes;
	float seconds = (minutes - roundedMinutes) * 60.0f;
	int roundedSeconds = (int)seconds;

	FString HUDStringGameTime = FString::Printf(TEXT("%.2d : %.2d : %.2d"), roundedHours, roundedMinutes, roundedSeconds);
	DrawText(HUDStringGameTime, FColor::White, CurrentViewportSize.X * 0.50f - 50.0f, CurrentViewportSize.Y * 0.05f, HUDFont);
}