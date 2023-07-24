// Pong 3D HUD class for Pong 3D, created by Aaron Wilson, Wilson World Games. July 16th, 2023.
// Pong 3D HUD class is responsible for displaying the player's score and AI's score.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Pong3DHUD.generated.h"


UCLASS()
class PONG3D_API APong3DHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	APong3DHUD();

	virtual void DrawHUD() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UFont* HUDFont;
};
