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
			HelpText->SetText(FText::FromString("as you may know, tower of hanoi consists of three towers (pegs) and more than one rings."));
			break;
		case EDialogStage::Second:
			DialogStage = EDialogStage::Third;
			HelpText->SetText(FText::FromString("in this game, the three towers are replaced by a yard (blocked by fence in a square shaped). and rings are replaced by wood logs."));
			break;
		case EDialogStage::Third:
			DialogStage = EDialogStage::Fourth;
			HelpText->SetText(FText::FromString("A stone is placed in front of the yard. Step on this stone to get a wood log and step again to another stone to place the wood log."));
			break;
		default:
			HelpText->SetText(FText::FromString("place all the logs in the third yard (rightmost yard) in ascending order just like on how you will play tower oh hanoi. good luck and have fun!"));
			break;
	}
}