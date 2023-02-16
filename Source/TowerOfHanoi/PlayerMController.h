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

	UPROPERTY(EditAnywhere)
	class UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere)
	class UInputAction* AddDiscAction;

	UPROPERTY(EditAnywhere)
	class UInputAction* RemoveDiscAction;

	UPROPERTY(EditAnywhere)
	class UInputAction* MouseClickAction;

	UPROPERTY(EditAnywhere)
	class UInputAction* PickupAction;

	void OnClickStart();
	void OnClickTriggered();

	FHitResult Hit;
	float ClickTime, PressTime;
};
