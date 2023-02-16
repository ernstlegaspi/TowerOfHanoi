#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BiggerLogWidget.generated.h"

UCLASS()
class TOWEROFHANOI_API UBiggerLogWidget : public UUserWidget {
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	// Create a function to set the text of BiggerLogText variable
	UFUNCTION()
	FText SetBiggerLogText();

protected:
	// Declare a variable with a data type of text block widget
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* BiggerLogText;

	bool Initialize() override;
};
