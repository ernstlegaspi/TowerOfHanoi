#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BiggerLogWidget.generated.h"

UCLASS()
class TOWEROFHANOI_API UBiggerLogWidget : public UUserWidget {
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	FText SetBiggerLogText();

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* BiggerLogText;

	bool Initialize() override;
};
