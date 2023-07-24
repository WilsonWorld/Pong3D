// Pong 3D HUD class for Pong 3D, created by Aaron Wilson, Wilson World Games. July 16th, 2023.
// Pong 3D HUD class is responsible for displaying the player's score and AI's score.


#include "Pong3DHUD.h"
#include "AIPongPaddle.h"
#include "PlayerPongPaddle.h"
#include "Kismet/GameplayStatics.h"

APong3DHUD::APong3DHUD()
{
	//static ConstructorHelpers::FObjectFinder<UFont> Pong3DFont(TEXT("/ Game/Content/UI/Pong3DFont.Pong3DFont"));
	//HUDFont = Pong3DFont.Object;
}

void APong3DHUD::DrawHUD()
{
	Super::DrawHUD();

	APlayerPongPaddle* playerPaddle = Cast<APlayerPongPaddle>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerPongPaddle::StaticClass()));
	AAIPongPaddle* aiPaddle = Cast<AAIPongPaddle>(UGameplayStatics::GetActorOfClass(GetWorld(), AAIPongPaddle::StaticClass()));
	FString HUDString = FString::Printf(TEXT("[Player Score: %d] vs [AI Score: %d]"), playerPaddle->paddleScore, aiPaddle->paddleScore);

	DrawText(HUDString, FColor::White, 600, 50, HUDFont);
}