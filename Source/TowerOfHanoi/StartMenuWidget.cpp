#include "StartMenuWidget.h"
#include "Components/Button.h"

void UStartMenuWidget::NativeConstruct() {
	Super::NativeConstruct();

	if(StartButton) {
		// bind the start button
		StartButton->OnClicked.AddDynamic(this, &UStartMenuWidget::StartButtonOnClicked);
	}
}

void UStartMenuWidget::StartButtonOnClicked() {
	// make the variable true if the player clicks the start button
	bStartButtonClicked = true;
}