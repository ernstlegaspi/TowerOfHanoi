#include "StartMenuWidget.h"
#include "Components/Button.h"

void UStartMenuWidget::NativeConstruct() {
	Super::NativeConstruct();

	if(StartButton) {
		StartButton->OnClicked.AddDynamic(this, &UStartMenuWidget::StartButtonOnClicked);
	}
}

void UStartMenuWidget::StartButtonOnClicked() {
	UE_LOG(LogTemp, Warning, TEXT("Clickeddddd"));
}