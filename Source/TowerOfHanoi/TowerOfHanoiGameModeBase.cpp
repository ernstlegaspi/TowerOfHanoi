#include "TowerOfHanoiGameModeBase.h"
#include "BiggerLogWidget.h"
#include "FinishGameWidget.h"
#include "HelpMenuWidget.h"
#include "InputMenuWidget.h"
#include "LogCountWidget.h"
#include "StartMenuWidget.h"
#include "GameFramework/GameUserSettings.h"

ATowerOfHanoiGameModeBase::ATowerOfHanoiGameModeBase() {
	PrimaryActorTick.bCanEverTick = true;
}

void ATowerOfHanoiGameModeBase::BeginPlay() {
	Super::BeginPlay();

	HelpMenuClass = nullptr;
	InputMenuClass = nullptr;
	BiggerLogClass = nullptr;
	BiggerLogText = "";
	LogCount = 0;

	// get the user settings and make the game fullscreen
	if(GEngine) {
		if(UGameUserSettings* UserSettings = GEngine->GetGameUserSettings()) {
			UserSettings->SetScreenResolution(UserSettings->GetDesktopResolution());
			UserSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);
			// UserSettings->LoadSettings(false);
			// UserSettings->ApplySettings(false);
		}
	}

	if(IsValid(StartMenuBPWidget)) {
		// create a new widget and add it to viewport
		// this is the start button widget
		StartMenuClass = Cast<UStartMenuWidget>(CreateWidget(GetWorld(), StartMenuBPWidget));
		StartMenuClass->AddToViewport();
	}
}

void ATowerOfHanoiGameModeBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if(StartMenuClass != nullptr) {
		if(StartMenuClass->bStartButtonClicked) {
			// if the player click start
			// remove the start button
			StartMenuClass->RemoveFromParent();
			StartMenuClass->bStartButtonClicked = false;

			// and create a new widget and add it to viewport
			// this is the instruction stage
			HelpMenuClass = Cast<UHelpMenuWidget>(CreateWidget(GetWorld(), HelpMenuBPWidget));
			HelpMenuClass->AddToViewport();
		}
	}
	else {
		// if the player's current log is bigger than the log inside the yard
		if(BiggerLogText != "") {
			BiggerLogClass = Cast<UBiggerLogWidget>(CreateWidget(GetWorld(), BiggerLogBPWidget));
			BiggerLogClass->AddToViewport();
			if(LogCountClass != nullptr) LogCountClass->RemoveFromParent();
			LogCountClass = nullptr;
		}
		else {
			LogCountClass = Cast<ULogCountWidget>(CreateWidget(GetWorld(), LogCountBPWidget));
			LogCountClass->AddToViewport();
			if(BiggerLogClass != nullptr) BiggerLogClass->RemoveFromParent();
			BiggerLogClass = nullptr;
		}
	}

	if(HelpMenuClass != nullptr) {
		if(HelpMenuClass->bFifthStage) {
			// if the player has finished reading the instruction stage
			// remove the instruction stage from the viewport
			HelpMenuClass->RemoveFromParent();
			HelpMenuClass->bFifthStage = false;

			// and create a new widget and add it to viewport
			// this is where the player will pick a log count
			InputMenuClass = Cast<UInputMenuWidget>(CreateWidget(GetWorld(), InputMenuBPWidget));
			InputMenuClass->AddToViewport();
		}
	}

	if(InputMenuClass != nullptr) {
		if(InputMenuClass->bButtonClicked) {
			// if the player has already pick a log count
			// remove it from the viewport
			InputMenuClass->bButtonClicked = false;
			MinMoves = InputMenuClass->MinMoves;
			LogCount = InputMenuClass->LogCount;
			InputMenuClass->RemoveFromParent();
			StartMenuClass = nullptr;
		}
	}

	// if the player finishes the game, add to viewport the congratulations text
	if(bFinishGame) {
		FinishGameClass = Cast<UFinishGameWidget>(CreateWidget(GetWorld(), FinishGameBPWidget));
		FinishGameClass->AddToViewport();
		bFinishGame = false;
	}
}