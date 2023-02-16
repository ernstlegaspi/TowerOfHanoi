#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InputMenuWidget.generated.h"

UCLASS()
class TOWEROFHANOI_API UInputMenuWidget : public UUserWidget {
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	// declare a public float variable to get the log count that the player will play
	float LogCount;

	// if any button is clicked
	bool bButtonClicked;

	// assign the min moves of the specific log count
	int MinMoves;

protected:
	// declare a variable that has a button widget data type
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

	// create a function to bind with their specific button numbers
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

	// create a function to optimize the repitition of setting the values
	UFUNCTION()
	void SetValues(uint8 Num, int MM);

};
