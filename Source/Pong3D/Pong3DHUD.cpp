// Pong 3D HUD class for Pong 3D, created by Aaron Wilson, Wilson World Games. July 16th, 2023.
// Pong 3D HUD class is responsible for displaying the player's score and AI's score.

#include "Pong3DHUD.h"
#include "PongGameState.h"
#include "Engine.h"


APong3DHUD::APong3DHUD()
{
}

void APong3DHUD::DrawHUD()
{
	Super::DrawHUD();
	APongGameState* pGS = Cast<APongGameState>(GetWorld()->GetGameState());
	FString HUDString = FString::Printf(TEXT("[Player Score: %d] vs [AI Score: %d]"), pGS->PlayerPaddleRef->paddleScore, pGS->AIPaddleRef->paddleScore);
	const FVector2D viewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	DrawText(HUDString, FColor::White, viewportSize.Y * 0.5f, 50, HUDFont);
}