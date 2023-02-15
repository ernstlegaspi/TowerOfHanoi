#include "StartPawn.h"
#include "GameFramework/PlayerController.h"

AStartPawn::AStartPawn() {
	PrimaryActorTick.bCanEverTick = true;
}

void AStartPawn::BeginPlay() {
	Super::BeginPlay();

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