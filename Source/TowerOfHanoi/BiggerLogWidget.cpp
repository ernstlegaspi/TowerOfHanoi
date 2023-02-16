#include "BiggerLogWidget.h"
#include "TowerOfHanoiGameModeBase.h"
#include "Components/TextBlock.h"

void UBiggerLogWidget::NativeConstruct() {
	Super::NativeConstruct();
}

bool UBiggerLogWidget::Initialize() {
	bool Success = Super::Initialize();

	if(!Success) return false;

	BiggerLogText->TextDelegate.BindUFunction(this, "SetBiggerLogText");

	return true;
}

FText UBiggerLogWidget::SetBiggerLogText() {
	if(ATowerOfHanoiGameModeBase* GameMode = Cast<ATowerOfHanoiGameModeBase>(GetWorld()->GetAuthGameMode())) {
		return FText::FromString(GameMode->BiggerLogText);
	}

	return FText::FromString("Null");
}