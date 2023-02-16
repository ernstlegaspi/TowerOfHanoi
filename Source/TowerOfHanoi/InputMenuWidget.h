#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InputMenuWidget.generated.h"

UCLASS()
class TOWEROFHANOI_API UInputMenuWidget : public UUserWidget {
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	float LogCount;
	bool bButtonClicked;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button3;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button4;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button5;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button6;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button7;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button8;

	UPROPERTY()
	class APickupSpawner* Pickup;

	UFUNCTION()
	void Button3Click();

	UFUNCTION()
	void Button4Click();

	UFUNCTION()
	void Button5Click();

	UFUNCTION()
	void Button6Click();

	UFUNCTION()
	void Button7Click();

	UFUNCTION()
	void Button8Click();

	UFUNCTION()
	void SetValues(uint8 Num);

};
