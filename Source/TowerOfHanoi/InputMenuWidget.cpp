#include "InputMenuWidget.h"
#include "Components/Button.h"
#include "PickupSpawner.h"

void UInputMenuWidget::NativeConstruct() {
	Super::NativeConstruct();

	Button3->OnClicked.AddDynamic(this, &UInputMenuWidget::Button3Click);
	Button4->OnClicked.AddDynamic(this, &UInputMenuWidget::Button4Click);
	Button5->OnClicked.AddDynamic(this, &UInputMenuWidget::Button5Click);
	Button6->OnClicked.AddDynamic(this, &UInputMenuWidget::Button6Click);
	Button7->OnClicked.AddDynamic(this, &UInputMenuWidget::Button7Click);
	Button8->OnClicked.AddDynamic(this, &UInputMenuWidget::Button8Click);
}

void UInputMenuWidget::Button3Click() {
	SetValues(3);
}

void UInputMenuWidget::Button4Click() {
	SetValues(4);
}

void UInputMenuWidget::Button5Click() {
	SetValues(5);
}

void UInputMenuWidget::Button6Click() {
	SetValues(6);
}

void UInputMenuWidget::Button7Click() {
	SetValues(7);
}

void UInputMenuWidget::Button8Click() {
	SetValues(8);
}

void UInputMenuWidget::SetValues(uint8 Num) {
	LogCount = Num;
	bButtonClicked = true;
}