#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HelpMenuWidget.generated.h"

UENUM(BlueprintType)
enum class EDialogStage : uint8 {
	Default = 0,
	First = 1,
	Second = 2,
	Third = 3,
	Fourth = 4
};

UCLASS()
class TOWEROFHANOI_API UHelpMenuWidget : public UUserWidget {
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
	EDialogStage DialogStage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* HelpText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* NextButton;

	UFUNCTION()
	void NextButtonOnClicked();

};
