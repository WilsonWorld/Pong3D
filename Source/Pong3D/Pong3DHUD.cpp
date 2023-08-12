// Pong 3D HUD class for Pong 3D, created by Aaron Wilson, Wilson World Games. July 16th, 2023.
// Pong 3D HUD class is responsible for displaying the player's score and AI's score.

#include "Pong3DHUD.h"
#include "PongGameState.h"
#include "Engine.h"
#include "Components/Image.h"


APong3DHUD::APong3DHUD()
{
}

void APong3DHUD::DrawHUD()
{
	Super::DrawHUD();
	APongGameState* pGS = Cast<APongGameState>(GetWorld()->GetGameState());
	const FVector2D viewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	FString HUDStringPlayerScore = FString::Printf(TEXT("Player Score: %d"), pGS->PlayerPaddleRef->paddleScore);
	FString HUDStringComputerScore = FString::Printf(TEXT("Opponent Score: %d"), pGS->AIPaddleRef->paddleScore);
	FString HUDStringGameTime = FString::Printf(TEXT("%.2f"), pGS->GameTime);

	DrawRect(FLinearColor::Black, viewportSize.X * 0.25f, 47.5f, 130.0f, 30.0f);	// Color Background 
	DrawRect(FLinearColor::Black, viewportSize.X * 0.75f, 47.5f, 160.0f, 30.0f);	// Color Background 
	DrawRect(FLinearColor::Black, viewportSize.X * 0.50f - 25.0f, 47.5f, 100.0f, 30.0f);	// Color Background 

	DrawText(HUDStringPlayerScore, FColor::White, viewportSize.X * 0.25f, 50.0f, HUDFont);	// Text Foreground
	DrawText(HUDStringComputerScore, FColor::White, viewportSize.X * 0.75f, 50.0f, HUDFont);	// Text Foreground
	DrawText(HUDStringGameTime, FColor::White, viewportSize.X * 0.50f, 50.0f, HUDFont);	// Text Foreground
}