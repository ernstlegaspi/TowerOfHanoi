#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartMenuWidget.generated.h"

UCLASS()
class TOWEROFHANOI_API UStartMenuWidget : public UUserWidget {
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	bool bStartButtonClicked;

protected:
	// make a variable of button widget
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* StartButton;

	UFUNCTION()
	void StartButtonOnClicked();
};
