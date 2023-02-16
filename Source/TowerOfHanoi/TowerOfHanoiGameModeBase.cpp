#include "TowerOfHanoiGameModeBase.h"
#include "HelpMenuWidget.h"
#include "StartMenuWidget.h"

ATowerOfHanoiGameModeBase::ATowerOfHanoiGameModeBase() {
	PrimaryActorTick.bCanEverTick = true;
}

void ATowerOfHanoiGameModeBase::BeginPlay() {
	Super::BeginPlay();

	if(IsValid(StartMenuBPWidget)) {
		StartMenuClass = Cast<UStartMenuWidget>(CreateWidget(GetWorld(), StartMenuBPWidget));
		StartMenuClass->AddToViewport();
	}
}

void ATowerOfHanoiGameModeBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if(StartMenuClass->bStartButtonClicked) {
		StartMenuClass->RemoveFromViewport();
		StartMenuClass->bStartButtonClicked = false;
		HelpMenuClass = Cast<UHelpMenuWidget>(CreateWidget(GetWorld(), HelpMenuBPWidget));
		HelpMenuClass->AddToViewport();
	}
}