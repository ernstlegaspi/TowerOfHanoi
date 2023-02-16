#include "TowerOfHanoiGameModeBase.h"
#include "HelpMenuWidget.h"
#include "InputMenuWidget.h"
#include "StartMenuWidget.h"
#include "GameFramework/GameUserSettings.h"

ATowerOfHanoiGameModeBase::ATowerOfHanoiGameModeBase() {
	PrimaryActorTick.bCanEverTick = true;
}

void ATowerOfHanoiGameModeBase::BeginPlay() {
	Super::BeginPlay();

	HelpMenuClass = nullptr;
	InputMenuClass = nullptr;
	LogCount = 0;

	if(GEngine) {
		if(UGameUserSettings* UserSettings = GEngine->GetGameUserSettings()) {
			UserSettings->SetScreenResolution(UserSettings->GetDesktopResolution());
			UserSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);
			//UserSettings->LoadSettings(false);
			//UserSettings->ApplySettings(false);
		}
	}

	if(IsValid(StartMenuBPWidget)) {
		StartMenuClass = Cast<UStartMenuWidget>(CreateWidget(GetWorld(), StartMenuBPWidget));
		StartMenuClass->AddToViewport();
	}
}

void ATowerOfHanoiGameModeBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if(StartMenuClass->bStartButtonClicked) {
		StartMenuClass->RemoveFromParent();
		StartMenuClass->bStartButtonClicked = false;
		HelpMenuClass = Cast<UHelpMenuWidget>(CreateWidget(GetWorld(), HelpMenuBPWidget));
		HelpMenuClass->AddToViewport();
	}

	if(HelpMenuClass != nullptr) {
		if(HelpMenuClass->bFourthStage) {
			HelpMenuClass->RemoveFromParent();
			HelpMenuClass->bFourthStage = false;
			InputMenuClass = Cast<UInputMenuWidget>(CreateWidget(GetWorld(), InputMenuBPWidget));
			InputMenuClass->AddToViewport();
		}
	}

	if(InputMenuClass != nullptr) {
		if(InputMenuClass->bButtonClicked) {
			InputMenuClass->bButtonClicked = false;
			LogCount = InputMenuClass->LogCount;
			InputMenuClass->RemoveFromParent();
		}
	}
}