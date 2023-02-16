#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "PlayerMController.generated.h"

UCLASS()
class TOWEROFHANOI_API APlayerMController : public APlayerController {
	GENERATED_BODY()

public:
	bool bButtonPressed;

protected:
	APlayerMController();

	uint32 bMoveToCursor : 1;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	// assign the main input mapping context of the player
	UPROPERTY(EditAnywhere)
	class UInputMappingContext* MappingContext;

	// assign the mouse left click input action
	UPROPERTY(EditAnywhere)
	class UInputAction* MouseClickAction;

	// assign the R key input action
	UPROPERTY(EditAnywhere)
	class UInputAction* RestartGameAction;

	// assgin the T key input action
	UPROPERTY(EditAnywhere)
	class UInputAction* QuitGameAction;

	// get the main game mode
	UPROPERTY()
	class ATowerOfHanoiGameModeBase* GameMode;

	// create a function where the left click has start
	void OnClickStart();

	// create a function where the left click is triggered
	void OnClickTriggered();

	// create a function to bind with the R key
	void RestartGame(const FInputActionValue& Value);

	// create a function to bind with the T key
	void QuitGame(const FInputActionValue& Value);

	// create a variable of hit result to get the data of hit result
	FHitResult Hit;
	float ClickTime, PressTime;
};
