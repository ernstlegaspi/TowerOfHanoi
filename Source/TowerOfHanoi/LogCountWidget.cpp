#include "LogCountWidget.h"
#include "TowerOfHanoiGameModeBase.h"
#include "Components/TextBlock.h"

void ULogCountWidget::NativeConstruct() {
	Super::NativeConstruct();
}

bool ULogCountWidget::Initialize() {
	bool Success = Super::Initialize();

	if(!Success) return false;

	GameMode = Cast<ATowerOfHanoiGameModeBase>(GetWorld()->GetAuthGameMode());
	// Bind the function to the text block widget to set the text
	LogCount->TextDelegate.BindUFunction(this, "SetLogCount");
	MoveCount->TextDelegate.BindUFunction(this, "SetMoveCount");
	MinMoves->TextDelegate.BindUFunction(this, "SetMinMoves");

	return true;
}

FText ULogCountWidget::SetLogCount() {
	// Get the main game mode and access the public variable
	return FText::FromString(FString::FromInt(GameMode->LogCount));
}

FText ULogCountWidget::SetMoveCount() {
	// Get the main game mode and access the public variable
	return FText::FromString(FString::FromInt(GameMode->MovesCount));
}

FText ULogCountWidget::SetMinMoves() {
	return FText::FromString(FString::FromInt(GameMode->MinMoves));
}