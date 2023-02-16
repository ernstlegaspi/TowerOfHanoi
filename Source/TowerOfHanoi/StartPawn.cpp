#include "StartPawn.h"
#include "GameFramework/PlayerController.h"

AStartPawn::AStartPawn() {
	PrimaryActorTick.bCanEverTick = true;
}

void AStartPawn::BeginPlay() {
	Super::BeginPlay();

	// shows the mouse cursor of the game to click on the UI of the start of the game
	if(APlayerController* PlayerController = Cast<APlayerController>(GetController())) {
		PlayerController->bShowMouseCursor = true;
		PlayerController->DefaultMouseCursor = EMouseCursor::Default;
		PlayerController->bEnableMouseOverEvents = true;
	}
}

void AStartPawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AStartPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}