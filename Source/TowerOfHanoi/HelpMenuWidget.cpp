#include "HelpMenuWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UHelpMenuWidget::NativeConstruct() {
	Super::NativeConstruct();
	
	DialogStage = EDialogStage::First;

	if(NextButton) NextButton->OnClicked.AddDynamic(this, &UHelpMenuWidget::NextButtonOnClicked);
}

void UHelpMenuWidget::NextButtonOnClicked() {
	switch(DialogStage) {
		case EDialogStage::First:
			DialogStage = EDialogStage::Second;
			HelpText->SetText(FText::FromString("Press R to restart the game and press T to quit the game. Left click on the ground to move."));
			break;
		case EDialogStage::Second:
			DialogStage = EDialogStage::Third;
			HelpText->SetText(FText::FromString("As you may know, tower of hanoi consists of three towers (pegs) and more than one rings."));
			break;
		case EDialogStage::Third:
			DialogStage = EDialogStage::Fourth;
			HelpText->SetText(FText::FromString("In this game, the three towers are replaced by a yard (blocked by fence in a square shaped). And rings are replaced by wood logs."));
			break;
		case EDialogStage::Fourth:
			DialogStage = EDialogStage::Fifth;
			HelpText->SetText(FText::FromString("A stone is placed in front of the yard. Step on this stone to get a wood log and step again to another stone to place the wood log."));
			break;
		case EDialogStage::Fifth:
			HelpText->SetText(FText::FromString("Place all the logs in the third yard (rightmost yard) in ascending order just like on how you will play tower oh hanoi. Good luck and have fun!"));
			DialogStage = EDialogStage::Default;
			break;
		default:
			bFourthStage = true;
			break;
	}
}