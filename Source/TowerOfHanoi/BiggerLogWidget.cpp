#include "BiggerLogWidget.h"
#include "TowerOfHanoiGameModeBase.h"
#include "Components/TextBlock.h"

void UBiggerLogWidget::NativeConstruct() {
	Super::NativeConstruct();
}

bool UBiggerLogWidget::Initialize() {
	bool Success = Super::Initialize();

	if(!Success) return false;

	// Bind the function to the text block widget to set the text
	BiggerLogText->TextDelegate.BindUFunction(this, "SetBiggerLogText");

	return true;
}

FText UBiggerLogWidget::SetBiggerLogText() {
	// Get the main game mode and access the public variable
	if(ATowerOfHanoiGameModeBase* GameMode = Cast<ATowerOfHanoiGameModeBase>(GetWorld()->GetAuthGameMode())) {
		return FText::FromString(GameMode->BiggerLogText);
	}

	// can only go here if line 22 is false
	return FText::FromString("Null");
}