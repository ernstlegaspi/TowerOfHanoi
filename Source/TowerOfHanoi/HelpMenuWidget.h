#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HelpMenuWidget.generated.h"

// declare enum; to be use in the HelpMenuWidget.cpp
// this enum is a stage on where the player is in the instruction text
UENUM(BlueprintType)
enum class EDialogStage : uint8 {
	Default = 0,
	First = 1,
	Second = 2,
	Third = 3,
	Fourth = 4,
	Fifth = 5
};

UCLASS()
class TOWEROFHANOI_API UHelpMenuWidget : public UUserWidget {
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	// declare a boolean variable to be accessed in TowerOfHanoiGameModeBase.cpp
	bool bFifthStage;

protected:
	// will be used in HelpMenuWidget.cpp in a switch statement
	UPROPERTY()
	EDialogStage DialogStage;

	// declare a variable with a text block widget data type
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* HelpText;

	// declare a variable with a button widget data type
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* NextButton;

	// create a function to bind with the NextButton widget
	UFUNCTION()
	void NextButtonOnClicked();

};
