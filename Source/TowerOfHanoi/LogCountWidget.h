#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LogCountWidget.generated.h"

UCLASS()
class TOWEROFHANOI_API ULogCountWidget : public UUserWidget {
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	FText SetLogCount();

	UFUNCTION()
	FText SetMoveCount();

	UFUNCTION()
	FText SetMinMoves();

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* LogCount;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* MoveCount;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* MinMoves;

	UPROPERTY()
	class ATowerOfHanoiGameModeBase* GameMode;

	bool Initialize() override;
	
};
